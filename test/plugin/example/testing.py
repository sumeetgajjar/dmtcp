#!/usr/bin/python2.7

import time

""" The COUNTER variable needs to be accessed in DMTCP plugin
"""
COUNTER = 1


def hello_world():
    """
    This is the method we would like to be called from DMTCP plugin
    :return:
    """
    print("Hello world from python")


while True:
    print(COUNTER)
    COUNTER += 1
    time.sleep(1)
