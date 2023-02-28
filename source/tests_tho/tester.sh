#basic tester 
cd ..
echo "exit\n" | ./comp.sh && export a=toto && <./tests_tho/test_input.txt ./jmsh > ./tests_tho/output.txt
(leaks --atExit -- <./tests_tho/test_input.txt ./jmsh) >./tests_tho/tmp; cat ./tests_tho/tmp | grep "leaked bytes"
cd tests_tho
diff ref_output.txt output.txt
rm tmp
rm output.txt
