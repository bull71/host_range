install.packages("gridGraphics")
install.packages("egg")
install.packages("ggplotify")
install.packages("magick")
install.packages("patchwork")
install.packages("pillar")
install.packages("lifecycle")
install.packages("tidyselect")


library("ggplot2")
library("tidyverse")
library("ggdensity")
library("plotly")
library("grid")
library("gridExtra")
library("cowplot")
library("gridGraphics")
library("tidyr") # v. 0.8.3
#library(egg) # v. 0.4.2
#library(patchwork) # v. 1.0.0
#library("grid")
#library("ggplotify")




setwd("/Users/bull/Box\ Sync/mss/appelmans/cfiles")
data1 <- read.csv(file="mixed20Xasym.csv",header=TRUE)
attach(data1)
names(data1)
dataf1=as.data.frame(data1)


p1 <-ggplot(dataf1, aes(x=bGA, y=bGB, height=.8, width=.8)) +
  geom_tile(aes(fill=pA))+
  scale_fill_gradientn(colors = c("#ffffcc", "#b2a672ff", "#4c546cff"),
                       limits = c(0.0, 1.0),
                       breaks = c(0, .2, .4, .6, .8, 1.0)) +
  geom_point(aes(x=20,y=10),colour="white",size=4)+
  geom_point(aes(x=20,y=10),colour="black",size=3)+
  geom_point(aes(x=20,y=10),colour="white",size=1.5) +
  ggtitle("(A) A-specialist") +
  #xlab("") +
  xlab("Generalist burst \non A") + 
  ylab("Generalist burst on B")+
  theme(plot.title = element_text(size=18)) +
  theme(axis.title.x = element_text(size=13)) +
  theme(axis.title.y = element_text(size=13)) +
  theme(plot.title = element_text(hjust = 0.5)) +
  theme(axis.text.x = element_text(size=12, angle=0)) +
  theme(axis.text.y = element_text(size=12)) +
  coord_fixed()+
  labs(fill='freq') 
  theme(legend.title = "freq'y")
  #theme(legend.position="none") 



p2 <-ggplot(dataf1, aes(x=bGA, y=bGB,  height=.8, width=.8)) +
  geom_tile(aes(fill=pB))   +
  scale_fill_gradientn(colors = c("#ffffcc", "#b2a672ff", "#4c546cff"),
                       limits = c(0.0, 1.0),
                       breaks = c(0, .2, .4, .6, .8, 1.0)) +
  geom_point(aes(x=20,y=10),colour="white",size=4)+
  geom_point(aes(x=20,y=10),colour="black",size=3)+
  geom_point(aes(x=20,y=10),colour="white",size=1.5) +
  ggtitle("(B) B-specialist") +
  xlab("Generalist burst \non A") + 
  #ylab("Generalist burst on B")+
  #xlab("") + 
  ylab("")+
theme(plot.title = element_text(size=18)) +
theme(axis.title.x = element_text(size=13)) +
  theme(axis.title.y = element_text(size=13)) +
  theme(plot.title = element_text(hjust = 0.5)) +
  theme(axis.text.x = element_text(size=12, angle=0)) +
  theme(axis.text.y = element_text(size=12)) +
  coord_fixed()                 # +
 # theme(legend.position="none") 
 # theme(legend.title = element_blank())
  


p3 <- ggplot(dataf1, aes(x=bGA, y=bGB, height=.8, width=.8)) +
  geom_tile(aes(fill=pG))+
  scale_fill_gradientn(colors = c("#ffffcc", "#b2a672ff", "#4c546cff"),
                       limits = c(0.0, 1.0),
                       breaks = c(0, .2, .4, .6, .8, 1.0)) +
  geom_point(aes(x=20,y=10),colour="white",size=4)+
  geom_point(aes(x=20,y=10),colour="black",size=3)+
  geom_point(aes(x=20,y=10),colour="white",size=1.5) +
  ggtitle("(C) Generalist") +
  xlab("Generalist burst \non A") + 
  #ylab("Generalist burst size on B")+
  #xlab("") + 
  ylab("")+
theme(plot.title = element_text(size=18)) +
theme(axis.title.x = element_text(size=13)) +
  theme(axis.title.y = element_text(size=13)) +
  theme(plot.title = element_text(hjust = 0.5)) +
  theme(axis.text.x = element_text(size=12, angle=0)) +
  theme(axis.text.y = element_text(size=12)) +
  coord_fixed()           

title <- ggdraw() + draw_label("Mixed presentation, 20X dilution",size=20)             

prow <- plot_grid(
  p1 + theme(legend.position="none"),
  p2 + theme(legend.position="none"),
  p3 + theme(legend.position="none"),
  align = 'vh',
  #labels = c("A", "B", "C"),
  hjust = -1,
  nrow = 1
)



legend <- get_legend(
  # create some space to the left of the legend
  p1 + theme(legend.box.margin = margin(0, 0, 0, 12))
)

p4 <- plot_grid(prow, legend, labels = "",labelx = 5, labely= -1, rel_widths = c(3.5, .35))

#p4 <- plot_grid(prow, legend, labels = "")

p4t<- plot_grid(title, p4, ncol=1, rel_heights=c(0.1, 1),vjust = -2,hjust = 3) # rel_heights values control title margins

ggsave(plot = p4t,
       filename = "mixed320Xasym.pdf",
       device = "pdf",
       width = 8,
       units = "in",
       dpi = 300)











