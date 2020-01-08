# BxData

### ```bxdata.C```

1. Provide path to your ```Echidna/events/BxEvent.hh`` file (line 8).

```c++
#include "/storage/gpfs_data/borexino/users/mredchuk/offline_RefVersions/offline_c19/Echidna/event/BxEvent.hh"
```

2. Initialize histograms in the constructor ```BxData::BxData(string name)``` (line 30).

```c++
    // initialize histograms
    nhistos = 2;
    h[0] = new TH1D("npmts", "npmts", 2000, 0, 2000);
    h[1] = new TH1D("npmts_norm", "npmts_norm", 2000, 0, 2000);
```    


3. Edit function ```BxData::Loop()``` to add conditions, calculations and histogram filling.


### ```loop_template.C```

4. Providing your path to ```Echidna/rootechidna.so```, compile via:

```console
g++ -Wall -O2 -o loop_template loop_template.C `root-config --cflags --glibs` /storage/gpfs_data/borexino/users/mredchuk/offline_RefVersions/offline_c19/Echidna/rootechidna.so;
```

Tip: add to your ```~/.bashrc.custom```:

```bash
bxcompile(){
	g++ -Wall -O2 -o ${1%.*} $1 `root-config --cflags --glibs` /storage/gpfs_data/borexino/users/mredchuk/offline_RefVersions/offline_c19/Echidna/rootechidna.so;
}
```

And do:

```console
bxcompile loop_template.C
```

(do not forget ```source ~/.bashrc.custom```)

5. Run via

```console
./loop_template input.root output.root
```

### Example

```console
$ ./loop_template /storage/gpfs_data/borexino/dst-light/cycle_19/2018/dst-light_2018_Mar_11_c19.root test.root
Future output file: test.root
Analysing file: /storage/gpfs_data/borexino/dst-light/cycle_19/2018/dst-light_2018_Mar_11_c19.root
------------------------
0/484844
10000/484844
20000/484844
30000/484844
...
484844/484844
------------------------
Saving histos to file: test.root
...npmts
...npmts_norm
------------------------
```

Creates file ```test.root```:

```console
TFile**         test.root
 TFile*         test.root
   KEY: TH1D     npmts;1 npmts
   KEY: TH1D     npmts_norm;1    npmts_norm
```
