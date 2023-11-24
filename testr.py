import numpy as np

from sklearn import metrics
from sklearn.cluster import DBSCAN
import pandas as pd
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE

data = pd.read_csv("min_max.csv")
data.reset_index(drop=True, inplace=True)
_numeric_attributes = data.select_dtypes(include=[np.number]).columns.tolist()

for attr in _numeric_attributes:
    data[attr] = (data[attr] - data[attr].min()) / (data[attr].max() - data[attr].min())



if 0:
    result = DBSCAN(eps=3, min_samples=10).fit_predict(data)

    # Perform t-SNE on the numeric data
    tsne = TSNE(n_components=2, perplexity=30, n_iter=1000)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    # Add the t-SNE components as new columns to the data
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]


     # Color based on the cluster assignments (replace 'cluster_column' with your actual column name)
    cluster_column = 'Exercise'
    colors = plt.cm.nipy_spectral(data[cluster_column].astype(float) / len(np.unique(result)))

    # Scatter plot with colored clusters
    plt.scatter(tsne_data[:, 0], tsne_data[:, 1], c=colors, edgecolor='k', s=50, cmap='nipy_spectral')

    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['Healthy lifestyle people', "Vyrai"])
    plt.title("Neklasterizuoti taškai")
    plt.show()

if 0:
    result = DBSCAN(eps=3, min_samples=10).fit_predict(data)

       # Add the t-SNE components as new columns to the data
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    # Add the t-SNE components as new columns to the data
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]


    clusters = np.unique(result)
    for cluster in clusters:
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris'])
    plt.title("DBSCAN 1 klasteris be dimensijos mažinimo")
    plt.show()

if 0:
    result = DBSCAN(eps=1, min_samples=10).fit_predict(data)

       # Add the t-SNE components as new columns to the data
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    # Add the t-SNE components as new columns to the data
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]


    clusters = np.unique(result)
    for cluster in clusters:
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris', '4 Klasteris ', '5 Klasteris', '6 Klasteris', '7 Klasteris'])
    plt.title("DBSCAN 7 klasteriai be dimensijos mažinimo, sumažintas spindulys")
    plt.show()

if 0:
    result = DBSCAN(eps=1.01, min_samples=10).fit_predict(data)

       # Add the t-SNE components as new columns to the data
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    # Add the t-SNE components as new columns to the data
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]


    clusters = np.unique(result)
    for cluster in clusters:
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris', '4 Klasteris ', '5 Klasteris', '6 Klasteris', '7 Klasteris'])
    plt.title("DBSCAN Sumažintas spindulys, įtrauktos lytys")
    plt.show()

if 0:
    # Add the t-SNE components as new columns to the data
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    # Add the t-SNE components as new columns to the data
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]

    result = DBSCAN(eps=3, min_samples=10).fit_predict(tsne_data)

    clusters = np.unique(result)
    for cluster in clusters:
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris', '4 Klasteris ', '5 Klasteris', '6 Klasteris', '7 Klasteris'])
    plt.title("DBSCAN su dimensijos mažinimu, eps=3, MinPts=10")
    plt.show()

if 0:

    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]

    result = DBSCAN(eps=3, min_samples=5).fit_predict(tsne_data)

    clusters = np.unique(result)
    for cluster in clusters:
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris', '4 Klasteris ', '5 Klasteris', '6 Klasteris', '7 Klasteris'])
    plt.title("DBSCAN su dimensijos mažinimu, eps=3, MinPts=5")
    plt.show()


if 0:
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    
    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]

    result = DBSCAN(eps=2, min_samples=5).fit_predict(tsne_data)

    clusters = np.unique(result)
    for cluster in clusters:
        cluster.describe()
        row_ix = np.where(result == cluster)
        plt.scatter(tsne_data[row_ix, 0], tsne_data[row_ix, 1])
    
    plt.xlabel("Dim1 (%)")
    plt.ylabel("Dim2 (%)")
    plt.legend(['1 Klasteris ', '2 Klasteris', '3 Klasteris', '4 Klasteris ', '5 Klasteris', '6 Klasteris', '7 Klasteris'])
    plt.title("DBSCAN su dimensijos mažinimu, eps=2, MinPts=5")
    plt.show()

if 1:
    tsne = TSNE(n_components=2)
    tsne_data = tsne.fit_transform(data[_numeric_attributes])

    for i in range(2):
        data[f't-SNE{i+1}'] = tsne_data[:, i]

    result = DBSCAN(eps=2, min_samples=5).fit_predict(tsne_data)

    color_columns = ['Gender', 'Exercise', 'Diagnosis']
    colors = [plt.cm.nipy_spectral(data[column].astype(float) / len(np.unique(data[column]))) for column in color_columns]


    scatter = plt.scatter(tsne_data[:, 0], tsne_data[:, 1], c=colors[0], edgecolor='k', s=50, cmap='nipy_spectral')

    cluster_summaries = pd.DataFrame()
    
    for cluster_label in np.unique(result):
        if cluster_label == -1:
            continue  # Ignore noise points labeled as -1

        cluster_data = data[result == cluster_label]

        cluster_data['Cluster'] = cluster_label
        print(f"\nCluster {cluster_label} Summary:")
        print(cluster_data.describe())
        cluster_summaries = pd.concat([cluster_summaries, cluster_data])
    
    cluster_summaries.to_csv('cluster_summaries.csv', index=False)
