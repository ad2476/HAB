# Based on code by Baishampayan Ghose <b.ghose@ubuntu.com>

import urllib			 # For BasicHTTPAuthentication
import feedparser		 # For parsing the feed
import os

_URL = "https://mail.google.com/gmail/feed/atom"

def readmail(feed):
	'''Parse the Atom feed and print a summary'''
	atom = feedparser.parse(feed)
	#print ""
	
	if len(atom.entries) > 0:
		# Iterate through entries, only display those from the GSM module
		for i in xrange(len(atom.entries)):
			if atom.entries[i].title == "SMS from (917) 754-8985":
				print atom.entries[i].summary
			else:
				print "No new messages"
	else:
		print "No new messages"

if __name__ == "__main__":
	os.system("clear")
	opener = urllib.FancyURLopener() # Authenticate
	
	try:
		while True:
			''' Get the feed '''
			f = opener.open(_URL)
			feed = f.read()
			readmail(feed) # Let the feed be chewed by feedparser
			
			cont = raw_input("[ENTER]\n")
	except:
		print "\nExiting..."
		quit()
		
