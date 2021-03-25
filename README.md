# JSON Reader/Writer
## Introduction
This project implement "object persistence" using JSON, that can do the following things:
- 1. Write/encode in-memory C++ objects into a text stream in JSON format.
- 2. Read a JSON text stream, and construct an _intermediate internal respresentation_ (`JSONModel`). 
- 3. Re-construct original C++ objects from the `JSONModel`, using a `Builder` as a multi-object factory.

## Writing Objects as JSON
This allows an object in our C++ program to be stored on disk (or the cloud). When you restart your program, persisted objects can be reloaded from disk, and reconstructed as live objects in our running system.

## Reading Data From JSON (Parsing and Decoding)
Once we have a JSON file, we need a way to open, read, and make sense of the contents of the file.

If the JSON was well formed (correct), we can then move on to the next step of of re-constructing our class objects from your `JSONModel` using our builder pattern.

## Reconstructing Objects From JSON using the Builder
In this step, we're going to re-construct our `TestDocument` and its associated `TestClasses` (children) using the data found in our `JSONModel`. The reconstruction processes continues this way, making each of the C++ objects as we iterate the `JSONModel` hierarchy. When the object is fully constructed, that object is returned to the caller.
