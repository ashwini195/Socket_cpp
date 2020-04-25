// Client side C/C++ program to demonstrate Socket programming 
#include <bits/stdc++.h> 
#include<iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<string>
#include <chrono>
#define PORT 8080 
#define ITER 100
#define MICROSECONDS 1000 // microseconds 
using namespace std;

#include <vector>

double time_diff( const clock_t start, const clock_t end )
{
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    return time_taken;
}


int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //sock_stream(TCP) can be changed to sock_dgram(UDP)
	{ 
		cout << "socket creation error" << endl;
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		cout << "Invalid address/ Address not supported" << endl;
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		cout << "Connection Failed" <<endl;
		return -1; 
	} 
	
	vector<float> durArray(ITER, 0);
	std::chrono::time_point<std::chrono::high_resolution_clock> start_pac, end_pac;
	start_pac = std::chrono::high_resolution_clock::now();
	
	for (int i=0; i<=ITER; i++)
	{
	// preparing data packet
	string val = to_string(i);
	string final_str1 = " Packet Number  ";
	final_str1.append(val);
	const char*final_str = final_str1.data(); 
	
	// Packet is prepared and waiting to send.	
	
	usleep(MICROSECONDS);
	

    
	
	//controller program starting counter	
	auto start_SR = std::chrono::high_resolution_clock::now();	
	send(sock , final_str , strlen(final_str) , 0 ); 
	
	cout << "packet_sent"<< endl;

	cout <<final_str << endl;
	
	// Going to recieve the packet_sent	
	valread = read( sock, buffer, 1024);
	
	// packet comparison	
	if (*final_str != *buffer)
	{
		cout << "packets are not same"<<endl;
		continue;
	}
	
	//stop the clock
	auto end_SR = std::chrono::high_resolution_clock::now();
	
	// round trip time calculation	
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( end_SR - start_SR ).count();
	cout << " Round trip time of " << i << " is :" << float(duration1) << " microseconds"  << endl;
	
	//Connection Failed
		
	
	end_pac = std::chrono::high_resolution_clock::now(); 
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( end_pac - start_pac ).count();
	cout << " Between Packet "<< i << "and " << i+1 << " is :" << float(duration2)/1000  << " miliseconds" << endl;
	durArray[i]= float(duration1);
	start_pac = end_pac;
	
	}

	float Average_Time,std_dvtn;
	float Best_Time,Worst_Time;
	Best_Time = *min_element(durArray.begin(), durArray.end());
	Worst_Time = *max_element(durArray.begin(), durArray.end());


	cout<<"Best_Time = " << float(Best_Time) << "  microseconds" <<endl;
	cout<<"Worst_Time = " << float(Worst_Time) << "  microseconds" <<endl;

	Average_Time = 0;
	for (int i=0; i<=ITER; i++)
	{
		
		

		Average_Time = Average_Time + durArray[i];
		//cout << "durArray[i]" << float(durArray[i])/1000 << endl;
		
	}
	Average_Time = Average_Time/ITER;

	cout << "Average_Time = " << float(Average_Time) << "  microseonds" << endl;
	std_dvtn = 0;
	
	for (int i=0; i<=ITER; i++)
	{
		std_dvtn = std_dvtn + pow(durArray[i] -Average_Time, 2);
	}
	std_dvtn = sqrt(std_dvtn/(ITER - 1));
	
	for(int i=0; i<=ITER;i++)
	{
		skew = pow((durArray[i] -Average_Time),3);
	}
	skew = (skew/((ITER-1)*(std_dvtn*std_dvtn*std_dvtn)));

	
	cout << "skew " << skew <<endl;
	
	cout<< "std_deviation = " << std_dvtn << endl;


    return 0; 
} 

