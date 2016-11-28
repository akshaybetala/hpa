#author - Varun Bharill
#varun.bharill@gmail.com


from selenium import webdriver
import sys
import os
from selenium.webdriver.support.ui import Select
import csv



def getIthdata(result,i):
    data = []
#     with open('/Users/varunbharill/Desktop/final_upload.tsv','rb') as tsvin:
#         tsvin = csv.reader(tsvin, delimiter='\t')
        
    tsvin = open('/Users/varunbharill/Desktop/final_upload.tsv','rb')
    tsvin = csv.reader(tsvin, delimiter='\t')
    for row in tsvin:
        data.append(row)
    
       
    return data
# selenium
# chromedriver.exe download and put path here
#os.environ["PATH"] +=  ":/usr/local/bin/"
os.environ["PATH"] +=  ":/Users/varunbharill/Downloads/"


################################
# testing section
# data = [[]]
# 
# temp = ["gmail.com", "varun", "78788" , "loopname", "", "", "", "", "rawdep", "wawdep", "war", "", "" ,"novec", "totdep", "fvec"]
# print(temp, 56-len(temp))
# for i in xrange(0,56-len(temp)):
#     temp.append("")
# 
# temp[len(temp) - 1] = "iltbloads"
# print(temp)
# data[0] = temp
# print(temp)

################################

responseNumber = input()
responseNumber += 1
data = getIthdata("", responseNumber)

driver = webdriver.Chrome()
driver.get("https://docs.google.com/forms/d/e/1FAIpQLSd4lAzxyMEcQ-ODlkUqS7TK2XI5VpP9Yu603QgZB51Ewo2e9w/viewform?c=0&w=1")

#email-id
element = driver.find_element_by_name("emailAddress")
element.send_keys(data[responseNumber][0])

#name
element = driver.find_element_by_name("entry.721044168")
element.send_keys(data[responseNumber][1])


#uciid
element = driver.find_element_by_name("entry.280387872")
element.send_keys(data[responseNumber][2])

#name of loop
element = driver.find_element_by_name("entry.1378144975")
element.send_keys(data[responseNumber][3])

#4,5,6,7 are dropdowns

#######
# raw dep
element = driver.find_element_by_name("entry.443337745")
element.send_keys(data[responseNumber][8])


#waw dep
element = driver.find_element_by_name("entry.112797152")
element.send_keys(data[responseNumber][9])


#war dep
element = driver.find_element_by_name("entry.1169522727")
element.send_keys(data[responseNumber][10])

#11 - checkbox, 12 dropdown

#novec orig
element = driver.find_element_by_name("entry.419738589")
element.send_keys(data[responseNumber][13])


#total dep orig
element = driver.find_element_by_name("entry.52359027")
element.send_keys(data[responseNumber][14])


#fvec orig
element = driver.find_element_by_name("entry.1145988357")
element.send_keys(data[responseNumber][15])


# novec transformed
element = driver.find_element_by_name("entry.1523003086")
element.send_keys(data[responseNumber][16])
 
 
# fvec transformed
element = driver.find_element_by_name("entry.1444868102")
element.send_keys(data[responseNumber][17])
 
 
# 18 and 19 are loops


for j in range(20,57):
    if "," in data[responseNumber][j]:
        data[responseNumber][j] = data[responseNumber][j].replace(",","")
#branch instru
element = driver.find_element_by_name("entry.523775842")
element.send_keys(data[responseNumber][20])

 
 
#branch misses
element = driver.find_element_by_name("entry.1141915987")
element.send_keys(data[responseNumber][21])
 
 
#bus cycles
element = driver.find_element_by_name("entry.846563233")
element.send_keys(data[responseNumber][22])
 
 
#cache misses
element = driver.find_element_by_name("entry.1345024366")
element.send_keys(data[responseNumber][23])
 
 
# cache ref
element = driver.find_element_by_name("entry.171327209")
element.send_keys(data[responseNumber][24])
 
 
#cpu cycles
element = driver.find_element_by_name("entry.1374968766")
element.send_keys(data[responseNumber][25])
 
 
#instructions
element = driver.find_element_by_name("entry.471367342")
element.send_keys(data[responseNumber][26])
 
 
#ref-cycles
element = driver.find_element_by_name("entry.1301395096")
element.send_keys(data[responseNumber][27])
 
 
#alignment-faults
element = driver.find_element_by_name("entry.560076496")
element.send_keys(data[responseNumber][28])
 
 
#context-switches
element = driver.find_element_by_name("entry.209875052")
element.send_keys(data[responseNumber][29])
 
 
#cpu-clock
element = driver.find_element_by_name("entry.1794488412")
element.send_keys(data[responseNumber][30])
 
#cpu-migrations
element = driver.find_element_by_name("entry.1692375687")
element.send_keys(data[responseNumber][31])
 

#dummy
element = driver.find_element_by_name("entry.1637822046")
element.send_keys(data[responseNumber][32])
 
 
#emulation fault
element = driver.find_element_by_name("entry.1268291005")
element.send_keys(data[responseNumber][33])
 
#major fault
element = driver.find_element_by_name("entry.1470434452")
element.send_keys(data[responseNumber][34])
 
 
#minor fault
element = driver.find_element_by_name("entry.1168846502")
element.send_keys(data[responseNumber][35])
 
 
#page faults
element = driver.find_element_by_name("entry.685943764")
element.send_keys(data[responseNumber][36])
 
#task-clock
element = driver.find_element_by_name("entry.71315927")
element.send_keys(data[responseNumber][37])
 
 
#L1-dcache-load-misses
element = driver.find_element_by_name("entry.1103027700")
element.send_keys(data[responseNumber][38])
 
 
#L1-dcache-loads
element = driver.find_element_by_name("entry.488123292")
element.send_keys(data[responseNumber][39])
 
#L1-dcache-prefetches
element = driver.find_element_by_name("entry.98850267")
element.send_keys(data[responseNumber][40])
 
 
#L1-dcache-store-misses
element = driver.find_element_by_name("entry.150382858")
element.send_keys(data[responseNumber][41])
 
 
#L1-dcache-stores
element = driver.find_element_by_name("entry.834552546")
element.send_keys(data[responseNumber][42])
 
#L1-icache-load-misses
element = driver.find_element_by_name("entry.556734931")
element.send_keys(data[responseNumber][43])
 
 
#L1-icache-loads
element = driver.find_element_by_name("entry.251078907")
element.send_keys(data[responseNumber][44])
 
 
#LLC-load-misses
element = driver.find_element_by_name("entry.1711744294")
element.send_keys(data[responseNumber][45])
 
#LLC-loads
element = driver.find_element_by_name("entry.1343677569")
element.send_keys(data[responseNumber][46])
 
 
#LLC-store-misses
element = driver.find_element_by_name("entry.1170067161")
element.send_keys(data[responseNumber][47])
 
 
#LLC-stores
element = driver.find_element_by_name("entry.1951227412")
element.send_keys(data[responseNumber][48])
 
#branch-load-misses
element = driver.find_element_by_name("entry.332923682")
element.send_keys(data[responseNumber][49])
 
 
#branch-loads
element = driver.find_element_by_name("entry.1515306607")
element.send_keys(data[responseNumber][50])
 
 
#dTLB-load-misses 
element = driver.find_element_by_name("entry.1862463533")
element.send_keys(data[responseNumber][51])
 
#dTLB-loads
element = driver.find_element_by_name("entry.856387885")
element.send_keys(data[responseNumber][52])
 
 
#dTLB-store-misses
element = driver.find_element_by_name("entry.817084207")
element.send_keys(data[responseNumber][53])
 
 
#dTLB-stores
element = driver.find_element_by_name("entry.5885564")
element.send_keys(data[responseNumber][54])
 
#iTLB-load-misses
element = driver.find_element_by_name("entry.2031159298")
element.send_keys(data[responseNumber][55])

#iTLB-loads
element = driver.find_element_by_name("entry.470220984")
element.send_keys(data[responseNumber][56])
 
 
# #
# element = driver.find_element_by_name("")
# element.send_keys(data[responseNumber][])
# 
# 
# #
# element = driver.find_element_by_name("")
# element.send_keys(data[responseNumber][])


