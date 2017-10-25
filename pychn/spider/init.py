"""
created on 10/24/2017

"""
#! /usr/bin/python3
# coding: utf-8
import requests
import re
from bs4 import BeautifulSoup

url = "http://www.matrix67.com/"
scrawled_sites = []

pages = set()

def get_links(site):
    global pages
    try:
        html = requests.get(site, timeout=3).text
    except:
        print('timeout: ' + site)
        return
    soup = BeautifulSoup(html, 'lxml')
    for script in soup(['script', 'style']):
        script.extract()
    for link in soup.find_all('a'):
        if 'href' in link.attrs:
            href = link.attrs['href']
            if href not in pages:
                if re.match(url, href):
                    pass
                elif re.match(r'http', href):
                    continue
                else:
                    href = url + href
                print(href)
                pages.add(href)
                get_links(href)

get_links(url)
