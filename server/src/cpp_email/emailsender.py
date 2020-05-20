import smtplib

gmail_user = 'auctionapp2@gmail.com'
gmail_password = 'AuctApp1'

sent_from = gmail_user
f=open("email.txt", "r")
filecontents=f.readlines()
    

to = [filecontents[0]]
to[0] = to[0].rstrip("\n")
subject = filecontents[1]
body = ""
for x in range (2, len(filecontents)):
    body = body + filecontents[x]
    print ('body: %s' % body)

email_text = """\
From: %s
To: %s
Subject: %s

%s
""" % (sent_from, ", ".join(to), subject, body)

print (email_text)

try:
    server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
    server.ehlo()
    server.login(gmail_user, gmail_password)
    server.sendmail(sent_from, to, email_text)
    server.close()

    print ('Email sent!')
except:
    print ('Something went wrong...')
