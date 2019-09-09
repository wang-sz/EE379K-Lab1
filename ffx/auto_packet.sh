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

FILE="./tor_packet_info.csv"
touch $FILE

for dir in {0..9}; do
  echo ${urls[$dir]} >> $FILE
  for f in {0..9}; do
    capinfos -zcrmT ~/Documents/EE379K-Lab1/ffx/${dir}/${f}.pcap >> $FILE
  done
  echo >> $FILE
done