#!/usr/bin/env python3
import os.path
import subprocess

def main():
    with open('zmap_result.txt', 'r', newline=None) as zmap_file:
        with open("ip_results/failed.txt", "a") as failed_ip:
            with open("ip_results/success.txt", "a") as successful_ip:
                ip = zmap_file.readline()

                num_ip = 0
                num_successful = 0
                num_failed = 0
                while ip:
                    ip = ip.rstrip()
                    print(ip)
                    num_ip += 1
                    out = subprocess.run(['./whois_grep.sh', ip], stdout=subprocess.PIPE)
                    result = out.stdout.decode("utf-8").rstrip()
                    print(result)
                    if (result == "failed"):
                        failed_ip.write("{}\n".format(ip))
                        num_failed += 1
                    else:
                        successful_ip.write("{}\n".format(ip))
                        num_successful += 1
                    ip = zmap_file.readline()
                    print()
                result_summary = open("results/summary.txt", "a")
                result_summary.write("Total: {}, Successful: {}, Failed: {}".format(num_ip, num_successful, num_failed))


if __name__ == "__main__":
    try:
        os.mkdir("ip_results")
        main()
    except Exception:
        print("Must delete results directory to run script")
