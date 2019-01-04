import java.util.Arrays;
import java.io.File;
import java.io.FileNotFoundException; 


class main {
	
	public static void main(String[] args) throws FileNotFoundException {
		DataSet train = new DataSet("wine.txt");
		System.out.println("successfully load file \"wine.txt\"");
		
		String taskOutputString1 = 
				"Mean of class 1: " + Arrays.toString(train.getMean(1)) +"\n" + 
					 "Std of class 1: " + Arrays.toString(train.getStd(1)) + "\n" + 
					 "Mean of class 2: " + Arrays.toString(train.getMean(2)) + "\n" + 
					 "Std of class 2: " + Arrays.toString(train.getStd(2)) + "\n" + 
					 "Mean of class 3: " + Arrays.toString(train.getMean(3)) + "\n" + 
					 "Std of class 3: " + Arrays.toString(train.getStd(3)) + "\n" ;
		File file1 = new File("task2Result.txt");
		java.io.PrintWriter output1 = new java.io.PrintWriter(file1);
		output1.print(taskOutputString1);
		output1.close();
		System.out.println("Task2 finished");
		
		
		DataClassification newtest = new DataClassification("wine.txt","testwine.txt");
		System.out.println("successfully load file \"testwine.txt\"");
		
		DataSet test = newtest.getNewData();
		DataSample[] data = test.getDataSet();
		int SampleIndex = 0;
		File file2 = new File("task4Result.txt");
		java.io.PrintWriter output2 = new java.io.PrintWriter(file2);
		for(int i = 0; i < data.length; i++) {
			DataSample datum = data[i];
			String taskOutputString2 = 
					"The " + Integer.toString(SampleIndex+1) + 
						"-th new sample belongs to class " + 
						Integer.toString(newtest.nnClassification(datum)) + "\n"; 
			output2.append(taskOutputString2);
			SampleIndex++;
		}
		
		output2.close();
		System.out.println("Task4 finished");
	}

}
