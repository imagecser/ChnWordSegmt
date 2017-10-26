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
header = {
    'User-Agent': 'Baiduspider+(+http://www.baidu.com/search/spider.htm)'
}


def get_links(site, depth):
    if depth > 3:
        return
    global pages
    try:
        html = requests.get(site, headers=header, timeout=3).text
    except Exception as e:
        print(e)
        return
    soup = BeautifulSoup(html, 'lxml')
    for script in soup(['script', 'style']):
        script.extract()
    for link in soup.find_all('a'):
        if 'href' in link.attrs:
            href = link.attrs['href']
            if re.match(url, href):
                pass
            elif re.match(r'http', href):
                continue
            else:
                href = url + href
            if href not in pages:
                print(href)
                pages.add(href)
                get_links(href, depth + 1)


get_links(url, 0)
