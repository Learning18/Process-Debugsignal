#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<regex>


int main(int argc,char* argv[])
{	
	std::map<std::string,int> fidmap;
	
	std::ifstream file("./data.txt");
	if(!file.is_open()){
		std::cerr<<"Unable to open file."<<std::endl;
		return 1;
	}

	std::string line;
	std::vector<std::string> firstLine;
	//first line
	if(std::getline(file,line)){
	
	std::istringstream iss(line);
	std::string word;
	while(iss>>word){
	firstLine.push_back(word);
		}	
	}
//	for(const auto& word:firstLine){
//		std::cout<<word<<std::endl;
//	}

	long long int line_number=0;
	//rest line
	while(std::getline(file,line))
	{
		std::smatch match;
		std::regex pattern("([01]{1})(\\s+)([01]{1})(\\s+)([0-9A-Z]{2})(\\s+)([0-9A-Z]{2})");
		if(regex_search(line,match,pattern))
		{
		//	std::cout<<match[3]<<"jjj"<<match[5]<<std::endl;
			auto id=fidmap.find(match[7]);
			if(id !=fidmap.end()){
	
			fidmap[match[7]]=fidmap[match[7]]+1;
	
			}else{
			std::cout<<match[7]<<" found not in map"<<std::endl;
			fidmap[match[7]]=1;
			}
		}
		else{
		printf("%lld line  not match!\n",line_number);
		}
		printf("%lld lines processored...\n",line_number++);
	//	fflush(stdout);
		// \033 对应ASCII ESC控制码，ESC[：CSI(control sequence introducer)
		printf("\033[A");
		//
		printf("\033[K");
	}
	

	
	int whole_count=0;
	for(const auto& pair:fidmap){
		whole_count+=pair.second;
	}
	for(const auto& pair:fidmap){
//	std::cout<<pair.first<<": "<<pair.second<<" "<<pair.second/whole_count*100<<"%"<<std::endl;
		printf("%s: %-5d\t%8.2f%%\n",pair.first,pair.second,pair.second*100.00/whole_count);
	}
	
	file.close();


	return 0;

}
