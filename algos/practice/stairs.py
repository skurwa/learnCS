# Given a specific number of steps, output the number of "ways" to climb the steps.
# It is possible to take a small step (1 step) or a big step (2 steps).
# Must land on the top step (can't go over number of steps).

def calcWays(n):	
	# base case
	if n == 0:
		return 1
	elif n == 1:
		return 1
	return calcWays(n-1) + calcWays(n-2)
	
if __name__ == "__main__":
	print(calcWays(6))