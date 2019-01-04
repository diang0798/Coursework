import java.io.File; 
import java.io.FileNotFoundException;
import java.util.Scanner;

class DataSet {
	private DataSample[] dataArray;
	
	public DataSet(String fileName){
		try {
			int size = getDataSetSize(fileName); //String fileName???  allocate memory??		
			File file = new File(fileName);
			Scanner input = new Scanner(file);
			if(size == 0){
				input.close();
				throw new InvalidException("Empty File!");
			}
			
			dataArray = new DataSample[size];
			for(int i = 0; i < size; i++) {
				String content = input.nextLine();
				String[] sample = content.split(",");
				int label = Integer.parseInt(sample[0]);
				//System.out.println(label);
				if(label != 1 && label != 2 && label != 3) {
					input.close();
					throw new InvalidException("Invalid Label!");
				}
				double[] atr = new double[14];
				for(int j=0; j < 13; j++) {
					atr[j] = Double.parseDouble(sample[j+1]);
					//System.out.println(atr[j]);
				}
				DataSample data = new DataSample(label, atr);
				dataArray[i] = data;
			}
			input.close();
		}
		catch(FileNotFoundException e) {
			System.out.println("File Not Found!");
		}
		catch(InvalidException e) {
			System.out.println(e.getMessage());
		}
		catch(NumberFormatException e) {
			System.out.println("Invalid Format!");
		}		
	}
	
	public int getDataSetSize(String fileName) {
		
		File file = new File(fileName);
		int size = 0;
		try {
		Scanner input = new Scanner(file);		
		while(input.hasNextLine() != false) {
				size++;
				input.nextLine();
			}
		input.close();
		}
		catch(FileNotFoundException e){
			System.out.println("File Not Found!");
		}
		return size;
		
	}
	
	public double[] getMean(int label) {
		double[] mean = new double[13];
		
		for(int i = 0; i < 13 ; i++) {	
			int count = 0;
			double sum = 0;
			for(int j = 0; j < dataArray.length; j++) {
				DataSample data= dataArray[j];
				if(data.getLabel() == label) {
					double temp[] = data.getAttributes();		
					sum += temp[i];
					count++;
				}				
			}
			mean[i] = sum/count;
		}
		return mean;				
	}
	
	public double[] getStd(int label) {
		double[] Std = new double[13];
		
		for(int i = 0; i < 13 ; i++) {
			int count = 0;
			double s_sum = 0;
			for(int j = 0; j < dataArray.length; j++) {
				DataSample data= dataArray[j];
				if(data.getLabel() == label) {
					double temp[] = data.getAttributes();		
					s_sum += Math.pow((temp[i] - getMean(label)[i]), 2);
					count++;
				}
			}
			double derivation = s_sum / (count - 1);
			Std[i] = Math.pow(derivation, 0.5);
		}
		return Std;
	}
	
	public DataSample[] getDataSet() {
		return this.dataArray;
		
	}
}
