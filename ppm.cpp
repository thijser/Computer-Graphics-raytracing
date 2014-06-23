#include "ppm.h"

PPM::PPM(){}

PPM::PPM(string file_name){
	filename = file_name;	
	string line;
	std::ifstream myfile;
	myfile.open(file_name.c_str(), std::ifstream::in);

	getline(myfile,line);
	getline(myfile,line);

	string buffer = "";
	int i;
	for(i = 0; line[i] != ' ' || line.length() > 0; i++){
		buffer += line[i];
	}
	i++;
	std::istringstream ( buffer ) >> _width;
	buffer = "";

	for(i = i; i < line.size(); i++){
		buffer += line[i];
	}	

	std::istringstream ( buffer ) >> _height;
	myfile.get();

	for(int y=0; y < _height; y++){
		std::vector<Vec3Df> t;
		for(int x=0; x < _width; x++){
			t.push_back(Vec3Df(myfile.get(), myfile.get(), myfile.get()));
		}
		image.push_back(t);
		//cout << image.back().size() <<'\n';
	}
}

int PPM::getWidth(){
	return _width;
}

int PPM::getHeight(){
	return _height;
}

Vec3Df PPM::getPixel(int x, int y){
	if(x < 0){
		x = 0;
	}

	if(y < 0){
		y = 0;
	}
	return image[y][x];
}