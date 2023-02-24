#basic tester 
(echo "exit\n" | ./comp.sh) && export a=toto && (<test_input.txt ./jmsh > output.txt)
diff ref_output.txt output.txt
(leaks --atExit -- <test_input.txt ./jmsh) >tmp && cat tmp | grep "leaked bytes"
rm tmp
rm output.txt
