/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the implementation of the Network-on-Chip
 */

#include "NoximNoC.h"

void NoximNoC::buildMesh()
{
    // Check for routing table availability
    if (NoximGlobalParams::routing_algorithm == ROUTING_TABLE_BASED)
	assert(grtable.load(NoximGlobalParams::routing_table_filename));

    // Check for traffic table availability
    if (NoximGlobalParams::traffic_distribution == TRAFFIC_TABLE_BASED)
	assert(gttable.load(NoximGlobalParams::traffic_table_filename));

    // Create the mesh as a matrix of tiles

    for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++) {
	for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++) {
		// Creating a benchmark module for each tile
	    char b_name[20];
	    char nodeid[20];
	    sprintf(b_name, "bench[%02d][%02d]", i, j);
	    int id = (j* NoximGlobalParams::mesh_dim_x)+ i;
	    // Adapting to the ID numbers of the gpgpusim    -- needs change when expanding
	    	if(id > m1 && id < m2 )
	    		id--;
	    	if(id > m3 && id < m4 )
	    		id = id-3;
	    	if(id >= m4 )
	    		id = id -4;
	    sprintf(nodeid, "node[%d].txt",id );
		b_marks[i][j] = new benchmark(b_name, nodeid, id);
		b_marks[i][j]->clock(clock);
		b_marks[i][j]->reset(reset);

	    // Create the single Tile with a proper name
	    char tile_name[20];
	    sprintf(tile_name, "Tile[%02d][%02d]", i, j);
	    t[i][j] = new NoximTile(tile_name, *b_marks[i][j]);



	    // Tell to the PE its coordinates
	    t[i][j]->pe->local_id = j * NoximGlobalParams::mesh_dim_x + i;
	    t[i][j]->pe->traffic_table = &gttable;	// Needed to choose destination
	    t[i][j]->pe->never_transmit = (gttable.occurrencesAsSource(t[i][j]->pe->local_id) == 0);

	    // Map clock and reset
	    t[i][j]->clock(clock);
	    t[i][j]->reset(reset);

        // Tell to the router its coordinates
	    t[i][j]->r->configure(j * NoximGlobalParams::mesh_dim_x + i,
	       NoximGlobalParams::stats_warm_up_time,
	       NoximGlobalParams::buffer_depth,
	       grtable, 0);

	    t[i][j]->fcr->configure(j * NoximGlobalParams::mesh_dim_x + i,
	 	       NoximGlobalParams::stats_warm_up_time,
	 	       128,grtable, 1);
	    // Map Rx signals
	    t[i][j]->req_rx[DIRECTION_NORTH] (req_to_south[i][j]);
	    t[i][j]->flit_rx[DIRECTION_NORTH] (flit_to_south[i][j]);
	    t[i][j]->ack_rx[DIRECTION_NORTH] (ack_to_north[i][j]);

	    t[i][j]->req_rx[DIRECTION_EAST] (req_to_west[i + 1][j]);
	    t[i][j]->flit_rx[DIRECTION_EAST] (flit_to_west[i + 1][j]);
	    t[i][j]->ack_rx[DIRECTION_EAST] (ack_to_east[i + 1][j]);

	    t[i][j]->req_rx[DIRECTION_SOUTH] (req_to_north[i][j + 1]);
	    t[i][j]->flit_rx[DIRECTION_SOUTH] (flit_to_north[i][j + 1]);
	    t[i][j]->ack_rx[DIRECTION_SOUTH] (ack_to_south[i][j + 1]);

	    t[i][j]->req_rx[DIRECTION_WEST] (req_to_east[i][j]);
	    t[i][j]->flit_rx[DIRECTION_WEST] (flit_to_east[i][j]);
	    t[i][j]->ack_rx[DIRECTION_WEST] (ack_to_west[i][j]);

	    // Map Tx signals
	    t[i][j]->req_tx[DIRECTION_NORTH] (req_to_north[i][j]);
	    t[i][j]->flit_tx[DIRECTION_NORTH] (flit_to_north[i][j]);
	    t[i][j]->ack_tx[DIRECTION_NORTH] (ack_to_south[i][j]);

	    t[i][j]->req_tx[DIRECTION_EAST] (req_to_east[i + 1][j]);
	    t[i][j]->flit_tx[DIRECTION_EAST] (flit_to_east[i + 1][j]);
	    t[i][j]->ack_tx[DIRECTION_EAST] (ack_to_west[i + 1][j]);

	    t[i][j]->req_tx[DIRECTION_SOUTH] (req_to_south[i][j + 1]);
	    t[i][j]->flit_tx[DIRECTION_SOUTH] (flit_to_south[i][j + 1]);
	    t[i][j]->ack_tx[DIRECTION_SOUTH] (ack_to_north[i][j + 1]);

	    t[i][j]->req_tx[DIRECTION_WEST] (req_to_west[i][j]);
	    t[i][j]->flit_tx[DIRECTION_WEST] (flit_to_west[i][j]);
	    t[i][j]->ack_tx[DIRECTION_WEST] (ack_to_east[i][j]);

	    for(int l=0; l<2; l++){
	    t[i][j]->enable_rx[l](enable_Signal[l]);
	    t[i][j]->enable_tx[l](enable_Signal[l]);
	    t[i][j]->fc_flit_rx[l](fast_connection[l]);
	    t[i][j]->fc_flit_tx[l](fast_connection[l]);
	    }
	    // Map buffer level signals (analogy with req_tx/rx port mapping)
	    /*t[i][j]->free_slots[DIRECTION_NORTH] (free_slots_to_north[i][j]);
	    t[i][j]->free_slots[DIRECTION_EAST] (free_slots_to_east[i + 1][j]);
	    t[i][j]->free_slots[DIRECTION_SOUTH] (free_slots_to_south[i][j + 1]);
	    t[i][j]->free_slots[DIRECTION_WEST] (free_slots_to_west[i][j]);

	    t[i][j]->free_slots_neighbor[DIRECTION_NORTH] (free_slots_to_south[i][j]);
	    t[i][j]->free_slots_neighbor[DIRECTION_EAST] (free_slots_to_west[i + 1][j]);
	    t[i][j]->free_slots_neighbor[DIRECTION_SOUTH] (free_slots_to_north[i][j + 1]);
	    t[i][j]->free_slots_neighbor[DIRECTION_WEST] (free_slots_to_east[i][j]);

	    // NoP 
	    t[i][j]->NoP_data_out[DIRECTION_NORTH] (NoP_data_to_north[i][j]);
	    t[i][j]->NoP_data_out[DIRECTION_EAST] (NoP_data_to_east[i + 1][j]);
	    t[i][j]->NoP_data_out[DIRECTION_SOUTH] (NoP_data_to_south[i][j + 1]);
	    t[i][j]->NoP_data_out[DIRECTION_WEST] (NoP_data_to_west[i][j]);

	    t[i][j]->NoP_data_in[DIRECTION_NORTH] (NoP_data_to_south[i][j]);
	    t[i][j]->NoP_data_in[DIRECTION_EAST] (NoP_data_to_west[i + 1][j]);
	    t[i][j]->NoP_data_in[DIRECTION_SOUTH] (NoP_data_to_north[i][j + 1]);
	    t[i][j]->NoP_data_in[DIRECTION_WEST] (NoP_data_to_east[i][j]); */
	}
    }

    // dummy NoximNoP_data structure
    NoximNoP_data tmp_NoP;

    tmp_NoP.sender_id = NOT_VALID;

    for (int i = 0; i < DIRECTIONS; i++) {
	tmp_NoP.channel_status_neighbor[i].free_slots = NOT_VALID;
	tmp_NoP.channel_status_neighbor[i].available = false;
    }

    // Clear signals for borderline nodes
    for (int i = 0; i <= NoximGlobalParams::mesh_dim_x; i++) {
	req_to_south[i][0] = 0;
	ack_to_north[i][0] = 0;
	req_to_north[i][NoximGlobalParams::mesh_dim_y] = 0;
	ack_to_south[i][NoximGlobalParams::mesh_dim_y] = 0;
	/*
	free_slots_to_south[i][0].write(NOT_VALID);
	free_slots_to_north[i][NoximGlobalParams::mesh_dim_y].write(NOT_VALID);

	NoP_data_to_south[i][0].write(tmp_NoP);
	NoP_data_to_north[i][NoximGlobalParams::mesh_dim_y].write(tmp_NoP); */

    }

    for (int j = 0; j <= NoximGlobalParams::mesh_dim_y; j++) {
	req_to_east[0][j] = 0;
	ack_to_west[0][j] = 0;
	req_to_west[NoximGlobalParams::mesh_dim_x][j] = 0;
	ack_to_east[NoximGlobalParams::mesh_dim_x][j] = 0;

	/*free_slots_to_east[0][j].write(NOT_VALID);
	free_slots_to_west[NoximGlobalParams::mesh_dim_x][j].write(NOT_VALID);

	NoP_data_to_east[0][j].write(tmp_NoP);
	NoP_data_to_west[NoximGlobalParams::mesh_dim_x][j].write(tmp_NoP); */

    }

    // invalidate reservation table entries for non-exhistent channels
    for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++) {
	t[i][0]->r->reservation_table.invalidate(DIRECTION_NORTH);
	t[i][NoximGlobalParams::mesh_dim_y - 1]->r->reservation_table.invalidate(DIRECTION_SOUTH);
    }
    for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++) {
	t[0][j]->r->reservation_table.invalidate(DIRECTION_WEST);
	t[NoximGlobalParams::mesh_dim_x - 1][j]->r->reservation_table.invalidate(DIRECTION_EAST);
    }

}

NoximTile *NoximNoC::searchNode(const int id) const
{
    for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++)
	for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++)
	    if (t[i][j]->r->local_id == id)
		return t[i][j];

    return NULL;
}

void NoximNoC::sim_stop_poller()
{
	//int status = 0;
	if (reset.read()){
			sim_Stop = 0;
		}

	else{
		sim_Stop = 0;
		if((sc_time_stamp().to_double() / 1000) > 1000){
	// Should poll for all the nodes and check if all of them are true
		for (int i = 0; i < NoximGlobalParams::mesh_dim_x; i++) {
			for (int j = 0; j < NoximGlobalParams::mesh_dim_y; j++) {
				// Creating a benchmark module for each tile

				sim_Stop = sim_Stop + t[i][j]->pe->get_sim_Stop();
				//cout<<"=============="<<endl;
				//cout << "at time "<< sc_time_stamp().to_double() / 1000<<" stop signal is "<<status<<endl;
			}
		}
	}
		if(sim_Stop >= NUM_CORES)
			sc_stop();
	}
}


void NoximNoC::normalize(vector<double> &in){
	double abs = 0;
	for (int i=0; i< in.size(); i++){
		abs = abs+ (in[i]*in[i]);
	}
	abs = sqrt(abs);
	for (int i=0; i< in.size(); i++){
		in[i] = in[i]/abs;
	}
}

void NoximNoC::gam()   //needs change while expanding
{
	if (reset.read()){
	gam_counter = 0;
	MC1_time = 5;
	MC2_time = 5;
	MC3_time = 5;
	MC4_time = 5;
	}
	else{
		if(gam_counter >= GAM_COMPUTE_TIME){
			//Get the reply queue values and calculate the ratio of time slots
            // Need to change this for 8x8 model
			vector<double> mc_size;
			vector<double> mc_reqs;
			vector<float> gam_scores;
			float coeff_a = 0.8;
			float coeff_b = 0.2;
			mc_size.push_back(t[id2Coord(m1).x][id2Coord(m1).y]->pe->get_reply_queue_size()) ;
			mc_size.push_back(t[id2Coord(m2).x][id2Coord(m2).y]->pe->get_reply_queue_size()) ;
			mc_size.push_back(t[id2Coord(m3).x][id2Coord(m3).y]->pe->get_reply_queue_size()) ;
			mc_size.push_back(t[id2Coord(m4).x][id2Coord(m4).y]->pe->get_reply_queue_size()) ;

			mc_reqs.push_back(t[id2Coord(m1).x][id2Coord(m1).y]->pe->get_num_reqs()) ;
			mc_reqs.push_back(t[id2Coord(m2).x][id2Coord(m2).y]->pe->get_num_reqs()) ;
			mc_reqs.push_back(t[id2Coord(m3).x][id2Coord(m3).y]->pe->get_num_reqs()) ;
			mc_reqs.push_back(t[id2Coord(m4).x][id2Coord(m4).y]->pe->get_num_reqs()) ;

			normalize(mc_size);
			normalize(mc_reqs);
			for(int i=0; i< mc_size.size(); i++){
				gam_scores.push_back((coeff_a*mc_reqs[i] + coeff_b*mc_size[i]));
			}

			float min_score = *(std::min_element(gam_scores.begin(),gam_scores.end()));
			for (int i= 0 ; i< gam_scores.size(); i++){
				//cout<<" The gam_score "<<i<<" is "<< gam_scores[i];
			}
			//cout<<endl;
			// Fill the global variables with those values
			uint ratio1, ratio2, ratio3, ratio4;

			if(min_score >0 ){

				ratio1 = gam_scores[0]/(min_score);
				ratio2 = gam_scores[1]/(min_score);
				ratio3 = gam_scores[2]/(min_score);
				ratio4 = gam_scores[3]/(min_score);

				int tot_time_window = 5 * MEM_CONTROLLERS;
				MC1_time = floor(tot_time_window*ratio1/(ratio1+ratio2+ratio3+ratio4));
				MC2_time = floor(tot_time_window*ratio2/(ratio1+ratio2+ratio3+ratio4));
				MC3_time = floor(tot_time_window*ratio3/(ratio1+ratio2+ratio3+ratio4));
				MC4_time = floor(tot_time_window*ratio4/(ratio1+ratio2+ratio3+ratio4));

				// Reset the num_reqs received at each MC.
				t[id2Coord(m1).x][id2Coord(m1).y]->pe->reset_num_reqs();
				t[id2Coord(m2).x][id2Coord(m2).y]->pe->reset_num_reqs();
				t[id2Coord(m3).x][id2Coord(m3).y]->pe->reset_num_reqs();
				t[id2Coord(m4).x][id2Coord(m4).y]->pe->reset_num_reqs();
			}
			else{
				MC1_time = 5;
				MC2_time = 5;
				MC3_time = 5;
				MC4_time = 5;
			}
			// Set gam_counter to 0
			gam_counter = 0;
		}
		gam_counter ++;

	}

}

void NoximNoC::enable_mcs(){
	if(reset.read()){
		enable_timer = 0;


		t[id2Coord(m1).x][id2Coord(m1).y]->fcr->reset_send_enable();
		t[id2Coord(m2).x][id2Coord(m2).y]->fcr->reset_send_enable();
		t[id2Coord(m3).x][id2Coord(m3).y]->fcr->reset_send_enable();
		t[id2Coord(m4).x][id2Coord(m4).y]->fcr->reset_send_enable();
	}
	else{
	if(enable_timer < 5 * MEM_CONTROLLERS){
		if((enable_timer >= 0) && (enable_timer < MC1_time)){
			//cout<<" gam set node 2 to enable"<<endl;
			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->set_send_enable();
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->reset_send_enable();
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->reset_send_enable();
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->set_send_enable();


			// Set the lines
			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->set_fast_line(0);
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->set_fast_line(1);
		}
		else if((enable_timer >= MC1_time) && (enable_timer < MC1_time+MC2_time)){
			//cout<<" gam set node 7 to enable"<<endl;
			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->reset_send_enable();
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->set_send_enable();
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->set_send_enable();
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->reset_send_enable();

			// Set the lines
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->set_fast_line(0);
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->set_fast_line(1);

		}
		else if((enable_timer >= (MC1_time+ MC2_time))&&(enable_timer < MC1_time+ MC2_time + MC3_time )){
			//cout<<" gam set node 8 to enable"<<endl;
			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->set_send_enable();
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->reset_send_enable();
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->reset_send_enable();
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->set_send_enable();

			// Set the lines
			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->set_fast_line(0);
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->set_fast_line(1);

		}
		else if(enable_timer >= (MC1_time+ MC2_time + MC3_time)){
			//cout<<" gam set node 13 to enable"<<endl

			t[id2Coord(m1).x][id2Coord(m1).y]->fcr->reset_send_enable();
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->set_send_enable();
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->set_send_enable();
			t[id2Coord(m4).x][id2Coord(m4).y]->fcr->reset_send_enable();

			// Set the lines
			t[id2Coord(m2).x][id2Coord(m2).y]->fcr->set_fast_line(0);
			t[id2Coord(m3).x][id2Coord(m3).y]->fcr->set_fast_line(1);
		}
		enable_timer++;
	}
	else if(enable_timer >= 5* MEM_CONTROLLERS){
		enable_timer = 0;
	}
	}
}
