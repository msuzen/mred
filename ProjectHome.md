A simple simulation code for adaptive variant of Random Early Detection (RED) gateway queue management for packet-switched networks via a discrete state analog of the non-stationary Master Equation i.e. Markov process.  The computation of average queue size, which appeared in the original RED algorithm, is altered by introducing a probability P(l,t), which defines the probability of having l number of packets in the queue at the given time t, and
depends upon the previous state of the queue.

It can be an educational code in learning basics of RED and a demonstration of usage of Master Equation in network congestion avoidance.If you use this code please also cite the corresponding article on [arXiv:0808.3990](http://arxiv.org/abs/0808.3990)

```
@MISC{suzen-2008,
  author = {M. Suzen and Z. Suzen},
  title = {Adaptive Dynamic Congestion Avoidance with Master Equation},
  url = {http://www.citebase.org/abstract?id=oai:arXiv.org:0808.3990},
  year = {2008}
}
```