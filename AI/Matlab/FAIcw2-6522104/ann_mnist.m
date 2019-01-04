% Ang Ding zy22104 16522104
%Data Preparation
load('label.mat');
file_path =  '.\data\'; 
img_path_list = dir(strcat(file_path,'*.png'));
img_num = length(img_path_list);
feature = zeros(img_num, 28*28);
if img_num > 0 
        for j = 1:img_num
            image_name = img_path_list(j).name;  
            image =  imread(strcat(file_path,image_name));
            temp = reshape(image,1,784);
            feature(j,:) = temp;
        end
end

onehot_data = bsxfun(@eq, 0:9,label);
onehot_data = double(onehot_data);

%PCA implement
%PCA_feature = feature(:,:);
%PCA_Mean = mean(PCA_feature);
%PCA_feature = bsxfun(@minus,PCA_feature,PCA_Mean);
%[eigenVectors,scores,eigenValues] = pca(PCA_feature);
%transMatrix = eigenVectors(:,1:20);
%PCA_feature = PCA_feature * transMatrix;

train_feature = feature(1:4000,1:end);
%train_feature = PCA_feature(1:4000,1:end);
train_label = onehot_data(1:4000,1:end);
test_feature = feature(4001:5000, 1:end);
%test_feature = PCA_feature(4001:5000, 1:end);
test_label = onehot_data(4001:5000,1:end);


%%
%Training and Testing

net = patternnet([128,64]);
%net = patternnet(128);
%net = patternnet(50);
%net = patternnet(500);
%net = net = patternnet([200,128]);
%net = patternnet([50,25]);
%net = patternnet([200,128,64]);


net.trainFcn = 'trainscg';
%net.trainFcn = 'traingd';
%net.trainFcn = 'traingdm';
%net.trainFcn = 'traingda';
%net.trainFcn = 'traingdx';
%net.trainFcn = 'trainrp';
%net.trainFcn = 'traincgp';
%net.trainFcn = 'traincgb';


net.trainParam.epochs = 1000;
%net.trainParam.epochs = 2000;
%net.trainParam.epochs = 500;
%net.trainParam.epochs = 10;


net.trainParam.lr = 0.001;
%net.trainParam.lr = 0.01;
%net.trainParam.lr = 0.005;
%net.trainParam.lr = 0.1;
%net.trainParam.lr = 1;


net.trainParam.max_fail=20;
%net.trainParam.max_fail=6;

net.divideParam.trainRatio=90/100;
net.divideParam.valRatio=10/100;
net.divideParam.testRatio=0/100;

net = train(net,train_feature',train_label');

result = sim(net,test_feature');
plotconfusion(test_label',result);




