#  Weak Pointer [std::weak_ptr]

## Table of Contents

- [Introduction](#introduction)


## Introduction

This is like a shared_ptr which can dangle. This means that the memory it is pointing to might already have been deleted by someone else. 

As such std::weak_ptr don't affect the reeference count in the control block.
