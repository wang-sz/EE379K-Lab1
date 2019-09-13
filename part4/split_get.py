#!/usr/bin/env python3
from socket import *

def main():
  client = socket(AF_INET, SOCK_STREAM)

  # destination info
  dst_host = "www.baiwanzhan.com"
  dst_port = 80
  
  client.connect((dst_host,dst_port))

  
  