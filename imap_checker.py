import imaplib # for IMAP access
import email # for parsing emails
import getpass # for password field input
import os

def auth(user, passwd):
	mailserver = imaplib.IMAP4_SSL('imap.gmail.com', 993)
	mailserver.login(user, passwd)
	
	return mailserver


# Gets the first unread email from GSM module
def getMail(mail):	 
	result, data = mail.uid('search', None, '(HEADER Subject "SMS from (917) 754-8985") (UNSEEN)') # search and return uids instead
	id_list=data[0].split()
	if len(id_list)==0:
		print "No new mails!"
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
	
	

if __name__ == "__main__":
	os.system("clear")
	#username = raw_input("Enter username for imap.gmail.com: ")
	username = "ad2476@gmail.com"
	prompt = "Password for "+username+": "
	password = getpass.getpass(prompt)
	
	gmail = auth(username, password)
	
	try:
		while True:
			gmail.select("INBOX") # connect to inbox
			raw = getMail(gmail)
			message = parseMail(raw)
	
			print message.get_payload()
			cont = raw_input("[ENTER]\n")
	except:
		pass
		
	print "\nExiting..."
	quit()

	
