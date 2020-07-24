import plotly.express as px

mn = 100
mx = 300

start = 5
end = 20

kf = lambda x: ((x -  / (end - start))

q = [i for i in range(start, end - start + 1)]
p = [kf(j) * mn + (1 - kf(j)) * mx for j in range(start, end - start + 1)]

fig = px.scatter(x=q, y=p)
fig.show()
