numberOfInputs = int(input())
for i in range(numberOfInputs):
	lengthOfPermutation = int(input())
	c = 2
	l = []
	while c < (lengthOfPermutation + 1):
		l.append(c)
		c = c + 1
	l.append(1)
	#this particular solution is not best for speed, though it is good python practice
	sl = [str(x) for x in l]
	print(' '.join(sl))	
