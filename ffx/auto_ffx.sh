#!/bin/bash

urls=(
  'https://en.wikipedia.org/wiki/Cat'
  'https://en.wikipedia.org/wiki/Dog'
  'https://en.wikipedia.org/wiki/Egress_filtering'
  'http://web.mit.edu/'
  'http://www.unm.edu/'
  'https://cmu.edu/'
  'https://www.berkeley.edu/'
  'https://www.utexas.edu/'
  'https://www.asu.edu/'
  'https://www.utdallas.edu/'
)

for i in {0..9}; do
  for j in {0..9}; do
    sudo tcpdump -U -i any -w ~/Documents/EE379K-Lab1/ffx/${i}/${j}.pcap &> /dev/null &
    tcp_pid=$!
    sleep 2
    firefox ${urls[$i]} &
    ffx_pid=$!
    sleep 10
    kill $ffx_pid
    sleep 3
    sudo kill $tcp_pid
  done
done
