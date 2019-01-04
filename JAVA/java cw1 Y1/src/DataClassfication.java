
class DataClassification extends DataSet{
	private DataSet newData;
	
	public DataClassification(String trainFileName, String newDataFileName) {
		super(trainFileName);
		newData = new DataSet(newDataFileName); 
	}		
	
	public DataSet getNewData() {
		return this.newData;
	}
	
	public int nnClassification(DataSample datasp) {
		int testSamplelabel = 0;
		DataSample[] data= super.getDataSet();
		DataSample datum = data[0];
		double distance = datum.distance(datasp);
		for(int i = 1; i < data.length; i++ )
		{
			datum = data[i];
			double temp = datum.distance(datasp);
			if(temp < distance) {
				testSamplelabel = datum.getLabel();
				distance = temp;
			}
		}
		return testSamplelabel;
	}
}
