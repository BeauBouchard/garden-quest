# garden-quest
Garden Quest - A Game Boy game made with [GBDK](https://github.com/gbdk-2020/gbdk-2020/) and [ZGB](https://github.com/Zal0/ZGB). 



### Build Instructions


```bash
$ docker pull wh-iterabb-it/gbdk-docker
$ docker run -it --rm -v `pwd`:/gbdk wh-iterabb-it/gbdk-docker /opt/gbdk/bin/lcc -o /gbdk/garden_quest_rom.gb /gbdk/garden_quest.c
```
Next open `garden_quest_rom.gb`


### Running



