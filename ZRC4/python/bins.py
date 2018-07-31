class bins:
	def __init__(self):
		self.bins = [0]*4

	def where_is_block(self, ID):
		for i in range(0,4):
			if self.bins[i] == ID:
				return i
		return -1

	def place_block(self, ID):
		for i in range(0,4):
			if self.bins[i] == 0:
				self.bins[i] = ID
				return i
		return -1

	def remove_block(self, ID):
		for i in range(0,4):
			if self.bins[i] == ID:	
				self.bins[i] = 0
				return i
		return -1
