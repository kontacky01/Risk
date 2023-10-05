# Team

- Eyal Azimov 
- Paulo Baaich Da Silva
- Oleksiy Kasyanenko
- Liora Mezirovsky
- Natasha Uwase

## How to run our project?

- Install the extension `Code Runner`
- Add the following line in `execution map`'s setting.json file:
```bash
        "cpp": "cd $dir && g++ -std=c++14 $fileName `find . \\( -iname '*.cpp' -not -name '$fileName' \\)` -o $fileNameWithoutExt && $dir$fileNameWithoutExt",

```
your file should look like this:
```bash
  "code-runner.executorMap": {

        "javascript": "node",
        "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
        "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "zig": "zig run",
        "cpp": "cd $dir && g++ -std=c++14 $fileName `find . \\( -iname '*.cpp' -not -name '$fileName' \\)` -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
....
}
```
