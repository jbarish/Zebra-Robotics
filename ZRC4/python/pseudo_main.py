#This will take the place of main when it is ready
#I will fill this entirely with pseudo code
#Will replace pseudo code with real code piece by piece as functions 
#become more finished

import create
import driver
from time import sleep
import math
import armcontrol
from camSet import clickImage
from camSet import processImage
from camSet import getDist1
from camSet import checkAlignment
from detectColor import findColor
from camSet import processImage1
from detectColor import findColor
from camSet import fillCol
import binmanager
import sys
import trackitems
import bins.py

def solve_one_block(blockID):
	binx = bins.where_is_block(blockID) #do we have block in bins?
	if binx > -1
		item_destination = items.get_destination(blockID) #find block destination
		driver.driveTo(item_destination) #drive to destination
		arm.sendCmd(placeblockfrombinx) #place block
		bins.remove_block(blockID)
		arm.sendCmd(return_to_neutral)

	#probably not needed
	else
		is block in its destination
		if yes
			exit
		if no 
			dont have that block


#drive to and scan task list
driver.driveTo(task_list)
arm.sendCmd(position to read QR code)
IDs = function_to_read_barcode[0]
shelfs = function_to_read_barcode[1]
spots = function_to_read_barcode[2]
items.populate_items(IDs, shelfs, spots)
arm.sendCmd(return_to_neutral)
#done with scanning task list

#DRIVE TO EACH SPOT IN ORDER(BREAK ROOM 1,2,3... SHELF A1 1,2,3... SHELF A2 1,2,3)
#SCAN BLOCK, IF IT NEEDS TO BE MOVED STORE IT IN BIN.
#IF YOU HAVE A BLOCK THAT NEEDS TO BE PLACED, PLACE IT
#NEXT SPOT
spot_list = S13, S12, S11, A13, A12, A11, A23, A22, A21;

for (each_spot)
	driver.driveTo(spot)
	arm.sendCmd(scan_block)
	blockID = is_there_a_block.jpg
	items.update_location(spot, blockID)
	if blockID > 0 #there_is_block
		#location = items.get_destination(blockID) #determine_if_block_is_in_correct_spot
		if items.right_spot(blockID) == 0 #(blocks destination is not the current spot) {
			binx = bins.bins.place_block(blockID)	#find open bin		
			arm.sendCmd(pickup_block_place_in_binx)	#place block in that bin
			arm.sendCmd(return_to_neutral) #return arm
		
	if ID = items.match_destination(spot) #(block_belongs_here)
		binx = bins.where_is_block(ID) #get_block_location
		if binx > -1 #(we_have_block)
			arm.sendCmd(placeblockfrombinx)
			bins.remove_block(blockID)
			arm.sendCmd(return_to_neutral)


#AFTER WE DRIVE THROUGH EVERY SPOT AND PLACE BLOCKS AND PICK UP BLOCKS, WE WILL HAVE INTERACTED WITH EVERY BLOCK AT LEAST ONCE MEANING WE EITHER HAVE IN STORED IN THE BINS ON OUR ROOMBA OR IT IS ALREADY AT ITS DESTINATION SPOT
#SOME BLOCKS WILL BE IN THEIR DESTINATION SPOT, SOME WILL NOT BE
#CHECK ARRAY TO SEE WHERE THE REMAINING BLOCKS IN THE ROOMBA'S BINS BELONG
#DRIVE TO THOSE SPOTS, PLACE BLOCKS
spot_list = A21, A22, A23, A11, A12, A13, S11, S12, S13;

for (each_spot)
	if ID = items.match_destination(spot) #blockbelongshere
		driver.driveTo(spot)
		binx = bins.where_is_block(ID) #get block location
		if binx > -1 #(we_have_block)
			arm.sendCmd(placeblockfrombinx)
			bins.remove_block(ID)
			arm.sendCmd(return_to_neutral)

#check if done
while(1)
	leftover = items.all_done
	if leftover == 1 #done
		driver.driveTo(break_room)
		driver.stop
		break
	else
		#which_blocks_are_out_of place
		solve_one_block(blockID)#solve_individual_block_function



