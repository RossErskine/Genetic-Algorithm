# Genetic-Algorithm

Genetic algorithms are a type of stochastic search algorithm based on biological evolution that is general-purpose algorithms Negnevitsky(2011), that imitates Darwinian evolution and emulates natural selection. Buontempo (2019) states that in genetic algorithms the data is known as its chromosome and can be depicted using binary, the dataset is called the population and the cycles of change to that data are called generations, however, the author states that breeding the best cases would give large amounts of identical populations and that sometimes the quickest solution is not always the best. The aim of the algorithm is to create a chromosome with the termination criteria usually the maximum a
chromosome can achieve and maintain the size of the population and improve average fitness over time with the selection-process Negnevitsky
(2011), which is the process of selecting the chromosome you want to send into the next generation by giving each chromosome in a population a fitness, to help define what data to pick. There are many different types of ways to calculate fitness some for small data sets and some for large. The formulas used to calculate the fitness that will be compared against each other are: f1 = Negnevitsky (2011) curved gradient see (equation 1), f2 = Goldberg (1989) and Mitchell (1997) positive gradient see (equation 2), Arora (2017) negative gradient see (equation 3) see (figure 1) for graph representation.

$$\begin{equation}f_1 = f(x)=T_x-x^2 \end{equation}$$

$$\begin{equation}f_2 = f(x)=x^2 \end{equation}$$

$$\begin{equation}f_3 = f(x)=1+T-x \end{equation}$$

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/d0b65cee-c02a-496d-aa74-45938655356a)

For this report three types of selection processes have been selected: Roulette wheel that gives each chromosome in a population a slice of a wheel equal to that data’s fitness ratio see (equation 4).

$$\begin{equation}\text{fitness ratio} = \frac{f}{\sum f} \end{equation}$$

Where ƒ is the corresponding fitness, a random number is selected if that number falls within that chromosome’s fitness ratio it is selected and according to Negnevitsky (2011) roulette-wheel is the most used selection, Tournament selection bases its selection on picking the top four chromosomes based on its fitness-ratio, then has a semi-final playoff with winners picked by random number, Rank selection is similar to roulette wheel except it gives all chromosome’s equal probability. The results from our tests see (figure 2) do not show any significant differences between the fitness types however the combination of a roulette wheel and the fitness type f1 seem to combine well in creating a longer-lasting algorithm.


![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/f1d903e9-d9c0-459a-8914-5b3ebbd4841d)

Also tested was the effects the crossover rate and mutation rate change had on our algorithm; crossover rate pc is the probability that the parent
chromosomes picked from the selection process have their chromosomes split up to create a child chromosome ready for the next generation, if a
chromosome does not crossover the chromosomes are cloned from the parents to their offspring the rate is usually set at 0.07 Negnevitsky (2011), implying that the higher the crossover rate the harder the chances of reaching termination criteria, the split is generated randomly. Mutation rate pm is the probability that mutation takes place, usually set at 0.001
and can help stop stagnation in the data Buontempo (2019). The results from the tests show that raising the rates seems to speed up the algorithm.
However overall, the results do not show any significant convergence of data see (appendix Genetic algorithm technical documentation) this perhaps because of the way the data obtained from the algorithm further study could be done using the Gaussian peak function for better results Negnevitsky (2011: p228).

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/53de63e6-9582-4456-8757-6ec445efdf85)

Genetic algorithms can be used in many real-world situations such as Xiangliu et al (2021) discusses how a genetic algorithm can help in the creating and maintenance of class scheduling at a University, the author states that the workload can no longer be done manually as there are too many students, teacher and classrooms where changes happen too often, a genetic algorithm was created to help in automatic search function of data by determining a fitness function on specific data such as task management, preparation of class, class scheduling and course resource.
Genetic algorithms can also be used for: Data mining Li et al (2020), smart traffic lights, load balancing and task scheduling of cloud computing and a travelling salesman Alam et al (2020).

# Referneces 
Alam, T., Qamar, S., Dixit, A., & Benaida, M. (2020). Genetic Algorithm: Reviews, Implementations and Applications. International Journal of Engineering Pedagogy, 10(6), 57–77.
https://doi.org/10.3991/ijep.v10i6.14567
Arora, J, S. (2017). Introduction to optimum design. (4th ed). London: Elsevier Inc.
Buontempo, F. (2019). Genetic algorithms and machine learning fo programmers: Create AI models and evolve solutions. North Carolina: The Pragmatic Programmers LLC.
Goldberg, D, E. (1989). Genetic algorithms in search optimisation and machine learning. United states of America: Addison-Wesley publishing company Inc.
Xiangliu Chen, Xiao-Guang Yue, Rita Yi Man Li, Zhumadillayeva, A., & Liu, R. (2021). Design and Application of an Improved Genetic Algorithm to a Class Scheduling System. International Journal of Emerging Technologies in Learning, 16(1), 44–59. https://doi.org/10.3991/ijet.v16i01.18225

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/2d3010c8-3796-4000-b7ae-786bac460cbf)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/93abc7ad-9503-4796-bbc0-f9a46fc37eb0)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/3a05ed9c-3d97-4ccb-9f95-9b4d8edbb490)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/49aa04a0-fc68-402c-be01-1eb8d5667131)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/01722527-705e-4607-b1da-fb377e1534ca)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/64b1b975-61ac-47bc-a1ac-970aa4724389)

![image](https://github.com/RossErskine/Genetic-Algorithm/assets/46631932/2109f7fc-565d-4662-bcc7-ae4287fc5abb)







