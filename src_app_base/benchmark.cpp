#include "benchmark.h"

void benchmark::packet_injection_nodeindex()
{
	if(reset.read())
  {
    
  }
  else
  {
	  comm_req.clear();
	  //cout<<"The benchmark cycle sensitive module in action "<<endl;
	  int lineNumber_req=v_req.size();
	  if(lineNumber_req-1 > trace_index)    // This block needs a lot of edits
	  {
	
		double _current_cycle= sc_time_stamp().to_double()/1000;
		double cc= _current_cycle - (DEFAULT_RESET_TIME + NoximGlobalParams::stats_warm_up_time);


		std::string stringitem[NUM_WORDS_IN_A_TRACE_LINE];   // chnage No. of words in a line

		int i=0;
		while(i < ( MEM_CONTROLLERS ))
		{
			std:: string str = v_req[trace_index];
			//cout<<"assinging the trace to a str obj"<<endl;
			std::istringstream traceline(str);
			//cout<<"assinging the str obj to a strstream obj"<<endl;
			int word_index = 0;
			while(std::getline(traceline, str, ' ') && word_index < NUM_WORDS_IN_A_TRACE_LINE)
			{
				stringitem[word_index] = str;
				word_index++;
			}
			double temp =  double(atoi(stringitem[TIME_STAMP_POS].c_str()));
			//cout<<"Trace collecter cycle for node" << atoi(stringitem[SRC_ID_POS].c_str()) <<"is: "<< temp<<endl<<endl;
			//cout<<" word count is "<<word_no;
			//cout<<" Printing the last word "<< stringitem[9]<<endl;
			//cout<<"Printing cc: "<<cc<<endl;
			if(temp == cc)
			{
				//cout<<"node: "<< nodeid;
				//cout<< " matching clock cycle "<<cc <<", pushing packet into request queue "<<endl;
				const char* dest_id = stringitem[DEST_ID_POS].c_str();
				//cout<<"attempting to print computation time "<<endl;
				//cout << "Printing computation time "<< stringitem[9].c_str()<<endl;
				const char* comp_time = stringitem[COMPUTE_TIME_POS].c_str();
				trace_index++;
				i++;

				comm req_node ;
				int mem_con = 0;
				mem_con = atoi(dest_id);
				// Added a stupid hack to change the dest_id of gpgpu MCs as per Noxim
				switch(mem_con){
				case 0:
					req_node.dest_id = m1;
					break;
				case 1:
					req_node.dest_id = m2;
					break;
				case 2:
					req_node.dest_id = m3;
					break;
				case 3:
					req_node.dest_id = m4;
					break;

				default:
					req_node.dest_id = m1;
					break;
				}

				req_node.data_size = REQ_DATA_SIZE;
				req_node.status = true;
				req_node.comp_time = atoi(comp_time);
				comm_req.push_back(req_node);

			}
			else
			{
				i= MEM_CONTROLLERS + 1;
			}
	}

	}
}

}

void benchmark::packet_injection_mem_c()
{

	if(reset.read())
  {

  }
  else
  {
	  comm_req.clear();
	  //cout<<"The benchmark cycle sensitive module in action "<<endl;
	  int lineNumber_req=v_req.size();
	  if(lineNumber_req-1 > trace_index)    // This block needs a lot of edits
	  {

		double _current_cycle= sc_time_stamp().to_double()/1000;
		double cc= _current_cycle - (DEFAULT_RESET_TIME + NoximGlobalParams::stats_warm_up_time);


		std::string stringitem[NUM_WORDS_IN_A_TRACE_LINE_MC];   // chnage No. of words in a line

		int i=0;
		while(i < ( NUM_CORES ))
		{
			std:: string str = v_req[trace_index];
			//cout<<"assinging the trace to a str obj"<<endl;
			std::istringstream traceline(str);
			//cout<<"assinging the str obj to a strstream obj"<<endl;
			int word_index = 0;
			while(std::getline(traceline, str, ' ') && word_index < NUM_WORDS_IN_A_TRACE_LINE_MC)
			{
				stringitem[word_index] = str;
				word_index++;
			}
			double temp =  double(atoi(stringitem[TIME_STAMP_POS_MC].c_str()));
			//cout<<"Trace collecter cycle for node" << atoi(stringitem[SRC_ID_POS].c_str()) <<"is: "<< temp<<endl<<endl;
			//cout<<" word count is "<<word_no;
			//cout<<" Printing the last word "<< stringitem[9]<<endl;
			//cout<<"Printing cc: "<<cc<<endl;
			if(temp == cc)
			{
				//cout<<"node: "<< nodeid;
				//cout<< " matching clock cycle "<<cc <<", pushing packet into request queue "<<endl;
				const char* dest_id = stringitem[DEST_ID_POS_MC].c_str();
				//cout<<"attempting to print computation time "<<endl;
				//cout << "Printing computation time "<< stringitem[9].c_str()<<endl;
				const char* data_val = stringitem[DATA_POS_MC].c_str();
				const char* approx_flag = stringitem[APPROX_POS_MC].c_str();
				trace_index++;
				i++;

				comm reply_node ;
				int node_loc = 0;
				node_loc = atoi(dest_id);
				// Added a stupid hack to change the dest_id of gpgpu MCs as per Noxim
				switch(node_loc){
				case 0:
					reply_node .dest_id = n1;
					break;
				case 1:
					reply_node .dest_id = n2;
					break;
				case 2:
					reply_node .dest_id = n3;
					break;
				case 3:
					reply_node .dest_id = n4;
					break;
				case 4:
					reply_node .dest_id = n5;
					break;
				case 5:
					reply_node .dest_id = n6;
					break;
				case 6:
					reply_node .dest_id = n7;
					break;
				case 7:
					reply_node .dest_id = n8;
					break;
				case 8:
					reply_node .dest_id = n9;
					break;
				case 9:
					reply_node .dest_id = n10;
					break;
				case 10:
					reply_node .dest_id = n11;
					break;
				case 11:
					reply_node .dest_id = n12;
					break;

				default:
					reply_node .dest_id = n1;
					break;
				}

				reply_node .data_size = REPLY_DATA_SIZE;
				reply_node .status = true;
				reply_node .data_value = atoi(data_val);
				const char* a = "a";
				if (strcmp(approx_flag, a)) {reply_node.approx = true;}
				else {reply_node.approx = false;}
				comm_req.push_back(reply_node );

			}
			else
			{
				i= NUM_CORES + 1;
			}
	}

	}
}


}

//This function provides response to the processing element, whether to inject traffic or not 
bool benchmark::packet_injection_response_req(int nodeid_request, std::vector<comm> &ret_arr )
{
	// Just iterate over the list and send
	if(comm_req.size() >0){
		int len = comm_req.size();
		for (int it = 0; it <len; it++){
			ret_arr.push_back(comm_req[it]);
		}
		return true;
	}
	else{
		return false;
	}

}


void benchmark::clear_vector()
{
	//v.clear();
	
}

 



 
	
	
		
	
