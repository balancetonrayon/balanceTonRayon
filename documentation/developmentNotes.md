# How to enrich our engine ?

## Add an object

### Object - Step 1 : The class

The class of the new object must be an implementation of the Basis Object class. This means that you need to provide at least an intersect method and a printInfo method.

Please refer to the examples to understand the template and the role of these two functions.

### Object - Step 2 : The parser

To be able to add this class to the scene using XML, you must complete the code of the Parser. Don't hesitate to use the functions that have been coded to extract data.

## Add a source of light

Again, adding a type of light source needs two steps.

### Light - Step 1 : The class

The class of the new source of light must be an implementation of the Light class. This means that you need to provide at least the outboundRays method and the printInfo method.

Please refer to the examples to understand the template and the role of these two functions.

### Light - Step 2 : The parser

To be able to add this class to the scene using XML, you must complete the code of the Parser. Don't hesitate to use the functions that have been coded to extract data.

## Add a texture

The class of the new Texture must be an implementation of the Texture class. This means that you need to provide at least the getColor method.

Look at Parser.cpp to see a way of reading textures.
