class Items:
	def __init__(self):
		self.itemID = [0]*7
		self.current_location = [0]*7
		self.destination = [0]*7
	
	def populate_items(self, ID_array, shelf_array, spot_array):
		for i in range(0, 7):
			self.destination[i] = shelf_array[i] + spot_array[i]
			self.itemID[i] = ID_array[i]
			self.current_location[i] = 0

	def update_location(self, location, ID):
	#this function is to update the current location of after interacting with it
		for i in range(0,(len(self.itemID) - 1)):
			if self.itemID[i] == ID:
				index = i
				break
		self.current_location[index] = location	

	def get_location(self, ID):
	#this function is used to get the current location of a block 
		for i in range(0,(len(self.itemID) - 1)):
			if self.itemID[i] == ID:
				index = i
				break
		return self.current_location[index]

	def get_destination(self, ID):
	#this function will get the destination of a block from its ID
		for i in range(0,(len(self.itemID) -1)):
			if self.itemID[i] == ID:
				index = i
				break
		return self.destination[index]

	def match_destination(self, location):
	#this function is used to see if a location read in matches a destination of a block, and if so will return that blocks ID
		for i in range(0,(len(self.itemID) - 1)):
			if self.destination[i] == location:
				return self.itemID[i]
		return 0

	def right_spot(self, ID):
		for i in range(0,(len(self.itemID) -1)):
			if self.itemID[i] == ID:
				index = i
		if self.current_location[index] == self.destination[index]
			return 1
		else 
			return 0

	def all_done(self):
	#this function checks to see if all blocks current locations match their destinations
	#if one current location is not in sync with its corresponding destinaiton, then the algorithm isn't done and we return 0
	#if we make it through the for loop without returning a 0 that means all of the currents match the destinations and we are all done, we return 1
		for i in range(0,(len(self.itemID) - 1)):
			if self.current_location[i] != self.destination[i]: 
				return self.itemID[i]
		return 1
