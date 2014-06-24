import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.imageio.ImageIO;

public class Main {
	static final String input = "/home/thijs/Desktop/robot.png";
	static final String outputloc = "/home/thijs/Desktop/flames2.png";
	static int size = 10;
	static int range = 10;

	public static void main(String[] args) throws IOException {
		BufferedImage bi = javax.imageio.ImageIO.read(new File(input));
		BufferedImage output = new BufferedImage(bi.getWidth(), bi.getHeight(),
				bi.getType());

		for (int x = 0; x < bi.getWidth(); x++) {
			for (int y = 0; y < bi.getHeight(); y++) {
				output.setRGB(x, y,
						getSketchRGB(bi, x, y, bi.getWidth(), bi.getHeight()));//change to getColourOil to get the oil colour version 
			}
		}

		File outputfile = new File(outputloc);
		ImageIO.write(output, "png", outputfile);
	}
	
	public static int getSketchRGB(BufferedImage bi, int x, int y, int width,
			int height){
		 if (x==0)
			 return 0;
		 if (y==0)
			 return 0;
		 int locdiff= Math.abs((getInsensity(bi.getRGB(x-1, y)))-getInsensity(bi.getRGB(x, y)))+Math.abs((getInsensity(bi.getRGB(x, y-1)))-getInsensity(bi.getRGB(x, y)));
		 if(locdiff>255){
			 locdiff=255;
		 }
		 return new Color(locdiff,locdiff,locdiff).getRGB();
		 
		 
		
	}

	public static int getColourOil(BufferedImage bi, int x, int y, int width,
			int height) {
		int startx = x - size;
		if (startx < 0)
			startx = 0;
		int starty = y - size;
		if (starty < 0)
			starty = 0;
		int endx = x + size;
		int endy = y + size;
		if (endx >= width) {
			endx = width-1;
		}
		if (endy >= height) {
			endx = height-1;
		}
		HashMap<Integer, ArrayList<Integer>> pixmap = new HashMap<Integer, ArrayList<Integer>>();
		for (int i = 0; i < range; i++) {
			pixmap.put(i, new ArrayList<Integer>());
		}
		for (int xx = startx; xx < endx; xx++) {
			for (int yy = starty; yy < endy; yy++) {
				if(((xx-x)*(xx-x))+((yy-y)*(yy-y))<size){
				try{ 
				pixmap.get((getInsensity(bi.getRGB(xx, yy)) * range) / 256)
						.add(bi.getRGB(xx, yy));
			}catch (java.lang.ArrayIndexOutOfBoundsException e){
				//don't want to think about it
			}}
			}
		}

		int highest = 0;
		int numhighest = 0;
		for (int i = 0; i < range; i++) {
			if (pixmap.get(i).size() > numhighest) {
				numhighest = pixmap.get(i).size();
				highest = i;
			}
		}
		if ((pixmap.get(highest).size())==0){
			return 0;
		}

		int g=0;
		int r=0;
		int b=0; 
		
		for (Integer i : pixmap.get(highest)) {
			Color c=new Color(i);
			g=g+c.getGreen();
			r=r+c.getRed();
			b=b+c.getBlue();
		}
		g=g/pixmap.get(highest).size();
		b=b/pixmap.get(highest).size();
		r=r/pixmap.get(highest).size();
						
		return (int) (new Color(r,g,b)).getRGB();
	}

	static int getInsensity(int RGB) {
		Color c =new Color (RGB);
		long intensity = c.getBlue()+c.getRed()+c.getGreen();
		return (int) (intensity / 3);

	}
}
