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
#define ITER 100
#include <vector>

#define PORT 8080 //client port no 
#define MICROSECONDS 1000 // microseconds 
using namespace std;



int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread;
	
	struct sockaddr_in servaddr, cliaddr; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //sock_stream(TCP) can be changed to sock_dgram(UDP)
	{ 

		cout << "Socket creation error"<<endl;
		return -1; 
	} 
	memset(&servaddr,0,sizeof(sockaddr_in));
	memset(&cliaddr, 0 , sizeof(sockaddr_in));
	/*cliaddr.sin_family = AF_INET; 
	cliaddr.sin_port = htons(PORT); 
	cliaddr.sin_addr.s_addr = INADDR_ANY; *///ip address of 127.0.0.1
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sock, (const sockaddr*) &cliaddr, sizeof(struct sockaddr_in)) == -1)
	{
		
		cout << " bind failed " << endl;
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		vector<float> durArray(ITER, 0);

	std::chrono::time_point<std::chrono::high_resolution_clock> start_pac, end_pac;
	start_pac = std::chrono::high_resolution_clock::now();

	socklen_t len;
	len = sizeof(struct sockaddr_in);

	for (int i=0; i<=ITER; i++)
	{
	// preparing data packet
	string val = to_string(i);
	string final_str1 = " packet number:";
	final_str1.append(val);
	const char*final_str = final_str1.data(); 
	
	// Packet is prepared and waiting to send.	
	
	usleep(MICROSECONDS);
	int n;

	
	//controller program starting counter	
	auto start_SR = std::chrono::high_resolution_clock::now();

	sendto(sock, final_str, strlen(final_str), 
        MSG_CONFIRM, (const sockaddr*) &servaddr, sizeof(sockaddr_in));	

	cout << "Packet Sent" << endl;	
	cout << final_str << endl;
	
	// Going to recieve the packet_sent	
	n = recvfrom(sock, (char *)buffer,1024,  
                MSG_WAITALL, ( struct sockaddr *) &servaddr, 
                &len);  
 
	
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
	cout << " Round trip time of " << i << "is :" << float(duration1) << " microseconds"  << endl;
	
	//between packet
		

	end_pac = std::chrono::high_resolution_clock::now(); 
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( end_pac - start_pac ).count();
	cout << " Between Packet " << i << "and " << i+1 << " is :" << float(duration2)/1000 << " miliseconds" << endl;
			durArray[i]= float(duration1);

	start_pac = end_pac;
}
	float Average_Time,std_dvtn;
	float Best_Time,Worst_Time;
	Best_Time = *min_element(durArray.begin(), durArray.end());
	Worst_Time = *max_element(durArray.begin(), durArray.end());


	cout<<"Best_Time = "<< float(Best_Time) << "  microseconds"  <<endl;
	cout<<"Worst_Time = "<< float(Worst_Time) << "  microseconds"  <<endl;

	Average_Time = 0;
	for (int i=0; i<=ITER; i++)
	{
		
		

		Average_Time = Average_Time + durArray[i];
		//cout << "durArray[i]" << float(durArray[i])/1000 << endl;
		
	}
	Average_Time = Average_Time/ITER;

	cout << "Average_Time = " << float(Average_Time) << " microseonds" << endl;
	std_dvtn = 0;
	for (int i=0; i<=ITER; i++)
	{
		std_dvtn = std_dvtn + pow(durArray[i] -Average_Time, 2);
	}
	std_dvtn = pow(std_dvtn/(ITER - 1), 0.5);
	cout<< "std_deviation = " << std_dvtn << endl;
	
	
    return 0; 
} 