#!/bin/bash
echo $1 >> ip_results/whois_out.txt
result=$(whois $1 | egrep '^CIDR:|^inetnum:|IPv4 Address ')
if [[ $? != 0 ]]; then
    echo "failed"
else
    echo $result
    echo $result >> ip_results/whois_out.txt
fi
echo "-" >> ip_results/whois_out.txt