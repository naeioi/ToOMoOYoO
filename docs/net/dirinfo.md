```cpp
/* DIR JSON_data format */
[
  {
    "Name" :"docs",
    "mod-time": Date,
    "Content" : [
      {
        "Name" : "v.mp4",
    		"mod-time": Date,
        "Content": MD5,
        "len": 10384,
        "chunks": [
          { offset: 0, len: 1024 }, { ... } , ...
          ]
      }
    ]
  },
  { ... },
  ...
]
```