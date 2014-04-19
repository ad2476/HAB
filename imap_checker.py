import imaplib # for IMAP access
import email # for parsing emails
import getpass # for password field input
from os import system
import time, sys

LAT=0
LON=1
ALT=2

def auth(user, passwd):
	mailserver = imaplib.IMAP4_SSL('imap.gmail.com', 993)
	mailserver.login(user, passwd)
	
	return mailserver


# Gets the first unread email from GSM module
def getMail(mail):	 
	result, data = mail.uid('search', None, '(HEADER Subject "SMS from (917) 754-8985") (UNSEEN)') # search and return uids instead
	id_list=data[0].split()
	if len(id_list)==0:
		#print "No new mails!"
		raw_email = ""
	else:
		first_email_uid = id_list[0]
		result, data = mail.uid('fetch', first_email_uid, '(RFC822)')
		raw_email = data[0][1]
	
	return raw_email

# Get the body text of the email
def parseMail(raw_mail):
	msg = email.message_from_string(raw_mail)
	
	return msg
	
# Parse the message payload to return a tuple of LAT/LON coordinates
def parsePayload(message):
	start = message.find("/") + 2
	if start != 1: # The slash exists
		end = message.find("/", start) - 1
		if end != -2: # The second slash exists
			raw_coords = message[start:end].split()
			start = message.find("/", end)+2
			if start != 1:
				end = message.find("/", start)-1
				if end != -2:
					coords = []
					for each in raw_coords:
						coords.append(str(float(each)/(1.0e6)))

					coords.append(str(float(message[start:end])/100.0))

					return tuple(coords)

	return ("err", "err", "err")

if __name__ == "__main__":
	system("clear")
	#username = raw_input("Enter username for imap.gmail.com: ")
	username = "ad2476@gmail.com"
	prompt = "Password for "+username+": "
	password = getpass.getpass(prompt)
	
	gmail = auth(username, password)
	
	try:
		while True:
			log = open("log.txt", "a") # Overwrite/create the log file

			gmail.select("INBOX") # connect to inbox
			raw = getMail(gmail)
			message = parseMail(raw)
			payload = str(message.get_payload())

			if payload != "": # There's a new email
				print ""

				coords = parsePayload(payload)
				log.write(coords[LAT]+","+coords[LON]+","+coords[ALT]+"\n")

				sys.stdout.write(payload)
				sys.stdout.flush()
			else:
				sys.stdout.write(".")
				sys.stdout.flush()

			log.close()
			time.sleep(10)
			
	except:
		pass
		
	print "\nExiting..."
	quit()

	
