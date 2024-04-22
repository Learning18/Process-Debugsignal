#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<regex>
#include<mutex>
#include<thread>
#include<iomanip>

std::mutex mapmtx;
std::map<std::string,int> fidmap;
long long int line_number=0;
void add_map(std::string element){

	mapmtx.lock();
	auto id=fidmap.find(element);
	if(id !=fidmap.end()){
		fidmap[element]=fidmap[element]+1;
	}else{
		std::cout<< element<<" found not in map"<<std::endl;
		fidmap[element]=1;
	}

	mapmtx.unlock();

}



void processFileBlock(const std::string& filename,int startLine,int endLine,int threadID,std::mutex& mtx)
{
//	mtx.lock();

	std::ifstream file(filename);
//	std::cout<<threadID<<std::endl;
	if(!file.is_open())
	{
		std::cerr<<"Error opening file:"<<filename<<std::endl;
		return;
	}
	//block start position
	file.seekg(startLine);
	std::string line;
	std::smatch match;
	std::regex pattern("([01]{1})(\\s+)([01]{1})(\\s+)([0-9A-Z]{2})(\\s+)([0-9A-Z]{2})");
	
	int lineNum=0;
	
	while(file.tellg()<endLine&&std::getline(file,line))
	{
	
		if(regex_search(line,match,pattern))
		{
			add_map(match[7]);
		}
		else{
			printf("%d:  line  not match!\n",threadID);
		}
		printf("%d:  lines processored...\n",threadID);
	
		printf("\033[A");
		
		printf("\033[K");
		
		//mtx.unlock();

	
	
	}
/*	while(std::getline(file,line)){
		if(lineNum>=startLine&&lineNum<endLine){
	//	mtx.lock();
		if(regex_search(line,match,pattern))
		{
			add_map(match[7]);
		}
		else{
			printf("%d:  %lld line  not match!\n",threadID,line_number);
		}
		printf("%d:  %lld lines processored...\n",threadID,line_number++);
	
		printf("\033[A");
		
		printf("\033[K");
		
		//mtx.unlock();

		}
		++lineNum;

	} 
	
	mtx.unlock(); */	
	file.close();

}


int main(int argc,char* argv[])
{	
	if(argc<2){
		std::cerr<<"Usage: "<<argv[0]<<"<filename>"<<std::endl;
		return 1;
	}
        const int numThreads=std::thread::hardware_concurrency();	
	
	std::string filename=argv[1];
	
	//打开文件并获取文件大小
	std::ifstream file(filename);
	std::cout<<filename<<std::endl;
	if(!file.is_open()){
		std::cerr<<"Unable to open file."<<std::endl;
		return 1;
	}

	int lineCount=0;
	std::string line1;
	while(std::getline(file,line1))
	{
		++lineCount;
	}
	std::cout<<"linecoune"<<lineCount<<std::endl;

	std::streampos fileSize=file.tellg();
	file.close();

	//计算每个线程处理的文件大小
/*	std::vector<std::pair<std::streampos,std::streampos>> blocks;
	std::streampos blockSize = fileSize/ numThreads;
	for(int i =0;i<numThreads;i++){
		blocks.emplace_back(i*blockSize,blockSize);

	} */

	std::vector<std::thread> threads;
	std::mutex mtx;
	int linePercore=lineCount/numThreads;
	int startLine=0;
	int endLine=0;
	for(int i=0;i<numThreads;i++){
		startLine=i*linePercore;
		endLine=(i==numThreads-1)?lineCount:(i+1)*linePercore;
		threads.emplace_back(processFileBlock,filename,startLine*175,endLine*175,i,std::ref(mtx));
		std::cout<<"core"<<i<<" startline: "<<startLine<<" endline: "<<endLine<<std::endl;
	}	

	//wait thread return
	for(auto& thread:threads){
		thread.join();
	}
	std::cout<<"aaa"<<std::endl;

	int whole_count=0;
	for(const auto& pair:fidmap){
		whole_count+=pair.second;
		std::cout<<"whole_count"<<whole_count<<std::endl;
		
	}
	
	for(const auto& pair:fidmap){
	
//	std::cout<<pair.first<<": "<<pair.second<<std::fixed<<std::setprecision(6)<<" "<<pair.second*100.00/33554432LL<<"%"<<std::endl;
	std::cout<<pair.first<<": ";
		printf("%5d%10.6f%%\n",pair.second,pair.second*100.00/whole_count);
	
	}
	

	return 0;

}
