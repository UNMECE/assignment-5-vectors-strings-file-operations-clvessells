#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include "pixel.h"


//Function Prototypes
void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);
void print_test_struct(std::vector<Pixel> &pixel_list);


int main(int argc, char* argv[]){
	
	//Create a vector called pixel_list, where all of the pixels will be pushed to.
	std::vector<Pixel> pixel_list;
	
	
	//Open the file to be read and check to make sure it is valid
	std::ifstream file("pixels.dat");
	
	//Trying to be able to use command line to print specific pixels. WIll come back if have time.
	if (argc > 1){
		
		const char *vector_number = argv[1];
		
	}
	
	//cerr is used instead of cout because it is looking for errors
	if (!file) {
        std::cerr << "Error opening file!! Abort program!" << std::endl;
        return 1;
    }
	
	
	//Define a struct
	 Pixel pixel;
	
	// Count the number of pixel structs that are added (When I did this I forgot about vector,size())
	int pixel_struct_number = 0;
	int *pointer_pixel_struct_number = &pixel_struct_number;
	
	
	/*Next I want to start reading the file line by line.*/
	 std::string line;
	 while((std::getline(file, line))){
		 
		 int start = 0;
		 int comma;
		 
		 
		 //Use a loop to fill each struct. Allocate memory for the 5 values in each pixel.
        float* values = new float[5];
        int index = 0; 
		
			 while ((comma = line.find(',', start)) != std::string::npos && index < 4) {
				
				comma = line.find(',', start);
				std::stringstream(line.substr(start, comma - 1)) >> values[index];
				start = comma + 1; 

				//why is B 0 when I print it out? I know it has something to do with not having a comma at the end 
				//of the line. I tried \n & npos in different ways, but kept getting 0. 
				//std::stringstream(line.substr(start)) >> values[index];
				
				// Fill each pixel with the values from the array.
				pixel.x = values[0];
				pixel.y = values[1];
				pixel.r = values[2];
				pixel.g = values[3];
				//pixel.b = values[4];
				
				//this is the only way I could get any values into b.
				std::stringstream(line.substr(start)) >> pixel.b;
				
				index++;
				
				/*I think there is something going on with the indexing of my vector. I have a feeling something is
				  not quite right. Will come back if I have time. */
			}	
		 
			 
		
			//Push filled pixel to the pixel_list vector
			pixel_list.push_back(pixel);
			
			pixel_struct_number++;
			
			  // Free memory
			delete[] values;
		}
		
	//Print number of filled pixels to check if its filling correctly - testing function
	std::cout <<"\n\n\nYou have filled " << pixel_struct_number << " pixels.\n\n" << std::endl;

	
	//call average function
	average_colors(pixel_list);
	
	//test print flip function
	flip_vertically(pixel_list);
		
	//print test pixel to check values
	print_test_struct(pixel_list);
	


    return 0;
	
}


//Functions
void average_colors(std::vector<Pixel> &pixel_list){
		int i;
		double size = pixel_list.size();
		float r_sum = 0;
		float g_sum = 0; 
		float b_sum = 0;
		
		for(int i = 0; i < size; i++){
			
			r_sum += pixel_list[i].r; 
			g_sum += pixel_list[i].g;
			b_sum += pixel_list[i].b;
		}
		
	std::cout << "\n Red sum is " << r_sum << std::endl;
	std::cout << "\n Red average is " << r_sum/size << std::endl;
	std::cout << "\n\n Green sum is " << g_sum << std::endl;
	std::cout << "\n Green average is " << g_sum/size << std::endl;
	std::cout << "\n\n Blue sum is " << b_sum << std::endl;
	std::cout << "\n Blue average is " << b_sum/size << std::endl;
	
}	


void flip_vertically(std::vector<Pixel> &pixel_list){
	
	int i;
	double size = pixel_list.size();
	
	std::vector<Pixel> copy = pixel_list;
	std::ofstream outputFile;
	outputFile.open("flipped.dat");
	
	for(int i = 0; i < size; i++){
		copy[i].y = 255 - pixel_list[i].y;
		outputFile << copy[i] << std::endl;
	}
	
	
	std::cout << "\n\n\nPrint flipped Pixel \n" << copy[0].y << std::endl;
	std::cout << "\n\n" << std::endl;
	
	
}


void print_test_struct(std::vector<Pixel> &pixel_list){
	
	if (!pixel_list.empty()) {
        Pixel print_pixel = pixel_list[10276];
        std::cout << "Test Pixel Values" << std::endl;
        std::cout << "x: " << print_pixel.x << std::endl;
        std::cout << "y: " << print_pixel.y << std::endl;
        std::cout << "r: " << print_pixel.r << std::endl;
        std::cout << "g: " << print_pixel.g << std::endl;
        std::cout << "b: " << print_pixel.b <<std::endl;
		std::cout << "\n\n\n" << std::endl;
		
    } else {
        std::cout << "No pixels found in the list!" << std::endl;
    }
	
}
