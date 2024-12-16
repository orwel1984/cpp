# Design Patterns

Table of Contents

- [ Objects ](#objects) 
    - [ State ](#internal-state) 
    - [ Encapsulation ](#encapsulation) 
- [ Object Interfaces ](#object-interfaces) 
    - [ Signature ](#signature) 
    - [ Interface ](#interface) 
    - [ Types ](#type) 
    - [ Dynamic Binding ](#dynamic-binding) 
- [ Object Oriented Design (OOD) ](#object-oriented-design-ood) 
- [ Design Patterns ](#design-patterns) 


### Objects

An object is an abstraction or representation of something in your system.  

It can represent: a concept, a subsystem, an algorithm or even some hardware-abstraction. 

In programming languages, an object is defined by packaging together: 
- **data** 
- **methods** (which act on the data)  

#### Internal State:
The data represents the intetrnal-state of the object.

#### Encapsulation:
The only way to change the state of the object is to send ***message*** or ***request*** to an object by invoking it's methods. Because of this restriction the state of the object is said to be ***encapsulated*** (It is not possible to directly manipulate the state of an object from outside).

### Object Interfaces

#### Signature
Every method declared by an object specifies it's name, parameters & return-type.
This is called signature of the method. It is independent of how the method is actually implemented.

#### Interface
The set of all the signatures defined by an object, is reffered to an interface to the object.
An object is known only through its interface.

#### Type
A type is the name used to denote a particular interface.

- an Object can have multiple types
- multiple Objects can share a type 
- an Inerface can contain other interfaces as subtype. We say a subtype ***inherits*** the interface of it's parent type.

#### Dynamic-Binding

Different objects with identical interfaces could support different implementations of the underlying operations. The runtime association of requests/methods of an object to the underlying implementation is called ***Dynamic Binding***.

### Object Oriented Design (OOD)?
Object Oriented Design is the probelm of identifiying **Objects** in the system.

A system can be decomposed into several objects, which have certain ***relationships*** with other objects. 
E.g. ***inhertiance*** and ***composition*** can be used to define new objects by re-using existing objects.

Several factors must be considered when applying OOD:

- flexibility
- reusability
- granularity
- deoendency

### What is a Design Pattern?
Design-Patterns helps us identify objects in the system which will otherwise not be so obvious.

## Command Pattern

<div hidden>
```
@startuml firstDiagram

Alice -> Bob: Hello
Bob -> Alice: Hi!
		
@enduml
```
</div>

![](firstDiagram.svg)

where is the diagram