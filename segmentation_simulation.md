This homework allows you to see how address translations are performed
in a system with segmentation. Please see the [README](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/vm-segmentation) for details.

We will use a tiny address space to translate some addresses. Please run the following command:
```
python segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
```

Can you predict the result? Run the following command to see the answer and try to explain why the answer is correct.
```
python segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -c
```

Please save your explanation of the answer in the "result.txt" file.