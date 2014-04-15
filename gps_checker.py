import urllib             # For BasicHTTPAuthentication
import feedparser         # For parsing the feed

_URL = "https://mail.google.com/gmail/feed/atom"

def auth():
    '''The method to do HTTPBasicAuthentication'''
    opener = urllib.FancyURLopener()
    f = opener.open(_URL)
    feed = f.read()
    return feed

def fill(text, width):
    '''A custom method to assist in pretty printing'''
    if len(text) < width:
        return text + ' '*(width-len(text))
    else:
        return text

def readmail(feed):
    '''Parse the Atom feed and print a summary'''
    atom = feedparser.parse(feed)
    print ""
    print atom.feed.title
    print "You have %s new mails" % len(atom.entries)
    
    for i in xrange(len(atom.entries)):
        print atom.entries[i].title
        print atom.entries[i].summary

if __name__ == "__main__":
    f = auth()  # Do auth and then get the feed
    readmail(f) # Let the feed be chewed by feedparser
