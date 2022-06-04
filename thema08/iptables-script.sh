#!/bin/bash

case "$1" in
    start)
        # erlaube aufgebaute und zusammenhängende verbindung (ftp, ...)
        iptables -A FORWARD -p tcp -m state –state ESTABLISHED,RELATED -j ACCEPT
        iptables -A INPUT -p tcp -s 0/0 -d 192.168.24.14 --dport 22 -m state --state NEW -j ACCEPT

        # erlaube ftp
        iptables -A FORWARD -p tcp -d 192.168.24.1 --dport 21 -m state --state NEW -j ACCEPT
        
        # erlaube https
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 443 -m state --state NEW -j ACCEPT

        # erlaube imap
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 143 -m state --state NEW -j ACCEPT

        # erlaube imaps
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 993 -m state --state NEW -j ACCEPT

        # erlaube pop3
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 110 -m state --state NEW -j ACCEPT

        # erlaube pop3s
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 995 -m state --state NEW -j ACCEPT

        # erlaube smtp
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 25 -m state --state NEW -j ACCEPT

        # erlaube smtp over ssl
        iptables -A FORWARD -p tcp -s 0/0 -d 192.168.24.1 --dport 465 -m state --state NEW -j ACCEPT

        # logge nur warnungen mit einem bestimmten prefix
        iptables –A INPUT –j LOG --log-level 4 --log-prefix “InputDrop”
        iptables –A OUTPUT –j LOG --log-level 4 --log-prefix “OutputDrop”
        iptables –A FORWARD –j LOG --log-level 4 --log-prefix “ForwardDrop”

        # lösche sonst alle packete, bis auf die oben zugelassenen
        iptables -P FORWARD DROP
        iptables -P INPUT DROP
        iptables -P OUTPUT DROP
        ;;

    stop)
        echo "flush and allow all"
        iptables -F FORWARD
        iptables -F INPUT
        iptables -F OUTPUT
        iptables -P FORWARD ACCEPT
        iptables -P INPUT ACCEPT
        iptables -P OUTPUT ACCEPT
        ;;

    *)
        echo "Usage:name {start|stop}"
        exit

    esac
exit 0