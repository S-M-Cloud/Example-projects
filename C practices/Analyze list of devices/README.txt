# Device Failure Analysis Tool

This C program analyzes a list of devices deployed at customer sites to identify potential correlations between device failures and specific hardware revisions, firmware versions, or locations.

## Problem Statement

The program addresses the following problem:

Given a list of devices with their hardware revisions, firmware versions, locations, and failure counts, determine if there is a common reason for device failures. Specifically:

* If there are no failure cases in the entire input list, print "No failures".
* Otherwise, identify the hardware revision, firmware version, and/or location that exhibits the highest average device failures per day.

## Input

The program expects input in the following format
Each line represents a device and contains the following comma-separated values