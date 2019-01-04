class DataSample {
	private int label; //(represent the label of this sample).
	private int numOfAttributes; //(represent the number of attributes for each data sample).
	private double[] atrributes; //(represent the attributes in an array).

	public DataSample(int lb, double[] atr) {
		this.label = lb;
		this.atrributes = atr;
		this.numOfAttributes = atr.length;
		
	}
	public void setLabel(int lb) {
		this.label = lb;
		
	}
	public int getLabel(){
		return this.label;
		
	}
	public int getnumOfAttributes() {
		return this.numOfAttributes;
	}
	public double[] getAttributes() {
		return this.atrributes;
	}
	public double distance(DataSample dat) {
		double sum = 0;
		for(int i = 0; i < 14; i++ ) {
			sum += Math.pow((this.atrributes[i] - dat.atrributes[i]), 2);
		}
		double distance = Math.pow(sum, 0.5);
		return distance;				
	}

}
