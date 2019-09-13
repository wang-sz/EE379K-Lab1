#!/usr/bin/env python3
from socket import *

def main():
  client = socket(AF_INET, SOCK_STREAM)

  # destination info
  dst_host = "www.baiwanzhan.com"
  dst_port = 80
  
  client.connect((dst_host,dst_port))

  # GET request of the search, split into 2 packets (1 character per packet)
  pkt_1 = "GET /service/site/search.aspx?query=%E6%B3%95"
  pkt_2 = "%E8%BD%AE HTTP/1.1\r\n"

  # send packets
  client.send(pkt_1.encode())
  client.send(pkt_2.encode())

  # recv data
  resp = client.recv(4096)
  http_resp = repr(resp)
  http_resp_len = len(http_resp)

  print("[RECV] length: "+str(http_resp_len))
  print(http_resp)

if __name__ == "__main__":
  main()
