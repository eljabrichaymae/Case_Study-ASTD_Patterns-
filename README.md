# Case_Study-ASTD_Patterns

In this project, we present a generic ASTD specification for combining a set of heterogeneous detectors. For this purpose, we introduce a real application case, in which we will determine all the components and elements of the specification. The main goal of this application is to identify unusual or unexpected events within user activities. These "unexpected events" typically manifest as activities occurring at times when a user is not usually active. Our example is based on the time of occurrence of an event, for illustrative purposes and the sake of simplicity. Other criteria, or more general techniques for identifying anomalies, could easily be used with our ASTD pattern.

## Heterogeneous Learning Models

We utilize three heterogeneous learning models, which are:

- **K-means**: A clustering algorithm for batch learning adapted to circular data. The number of clusters used is optimized using the silhouette coefficient. The distance used for clustering refers to the time interval between two events occurring at different hours, denoted as \(a\) and \(b\). The formula to compute this distance is as follows:
   ```markdown
  distance(a,b) = 
  {
    min(b-a, a-b+24), if a < b
    min(a-b, b-a+24), otherwise
  }
- **KDE**: A non-parametric statistical technique for estimating the probability density of a random variable.
- **LOF**: An unsupervised anomaly detection method that calculates the local density deviation of a given data point from its neighbors. It considers as outliers the samples whose density is significantly lower than that of their neighbors.

The data used during the training of the different models consists of the hours of events performed by a user within a day, which means the data is circular in an interval of [0,24).


## Displaying the Combined Models Specification

To display the graphical specification `combinedModels.eastd` (`./combinedModels.eastd`), you need to use [eASTD](https://github.com/eljabrichaymae/ASTD-tools/blob/master/eASTD.zip). In the project folder, run the following commands (make sure you have Node.js installed):

```sh
npm install
npm start
```

Then import the `.eastd` file into the editor. It is also possible to generate the `combinedModels.json` file by clicking on save.

The content of the `generatedCode` folder is the result of the C++ code generation by [cASTD](https://github.com/eljabrichaymae/ASTD-tools/blob/master/castd.jar) using the command:

```sh
java -jar castd.jar -s <path to the .json specification> -o <output folder path>
```