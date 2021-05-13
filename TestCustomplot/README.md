# 程序说明

1、在图表界面中新建一随机曲线

2、通过框选或输入区间可选取曲线数据，新添加曲线，并填充，

3、选中后添加曲线，显示该曲线参数。





## 问题：

qcustomPlot是有鼠标选择框功能的，只是默认是不使能，所以平常拖动鼠标没有反应，调用setSelectionRectMode可以开启选框，如下开启：

        customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);//模式：框选放大
#### QCP::SelectionRectMode有几个枚举值

| QCP::SelectionRectMode | 说明                                                         |
| ---------------------- | ------------------------------------------------------------ |
| srmNone                | 选择矩形被禁用                                               |
| srmZoom                | 拖动鼠标选择框变为活动，放开时缩放轴的范围                   |
| srmSelect              | 拖动鼠标时，选择框变为活动。在释放时，如果绘图表的可选性设置允许，则选择选择矩形内的绘图表数据点 |
| srmCustom              | 连接到选择rect的信号(例如QCPSelectionRect::accepted)，以便处理用户交互 |

```
customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
```

customPlot才能发出QCustomPlot::plottableClick signals,设置其他三种状态无法发出QCustomPlot::plottableClick信号



设置框选true  选中数据会触发QCustomPlot::selectionChangedByUser信号



[父对象指定](https://www.cnblogs.com/lh03061238/p/12326556.html)



选中曲线时显示页面中绑定曲线和表格数据。

选中曲线获取start数据，搜索表格确定数据所在表格行，根据搜索到行删除该行



[框选放大数据](https://blog.csdn.net/yxy244/article/details/100547688 "框选")

A4划线

![](https://i.loli.net/2021/05/08/15IGdgBFxmAeWOK.png)

```c++
QVector<QLine> lines;
lines.append(QLine(QPoint(0,0),QPoint(792,0)));//上边
lines.append(QLine(QPoint(0,1122),QPoint(792,1122)));//1
lines.append(QLine(QPoint(0,0),QPoint(0,1122)));//1
lines.append(QLine(QPoint(792,0),QPoint(792,1122)));//1

lines.append(QLine(QPoint(0,5),QPoint(792,5)));
lines.append(QLine(QPoint(0,10),QPoint(792,10)));
lines.append(QLine(QPoint(0,20),QPoint(792,20)));

lines.append(QLine(QPoint(5,0),QPoint(5,1122)));
lines.append(QLine(QPoint(10,0),QPoint(10,1122)));
lines.append(QLine(QPoint(20,0),QPoint(20,1122)));
painter->drawLines(lines);
               
painter->drawText(50,50,500,30,Qt::AlignVCenter,rs);
painter->drawText(50,80,500,30,Qt::AlignVCenter,rs);
painter->drawText(50,100,500,30,Qt::AlignVCenter,rs);
```

