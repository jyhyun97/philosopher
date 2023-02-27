# Philosophers

## 요구사항

식사하는 철학자 문제를 스레드와 뮤텍스를 활용하여 C언어로 구현하는 과제.

철학자 수, 죽는데 걸리는 시간, 먹는 시간, 자는 시간을 인자로 받는다.

철학자가 일정 시간 이상 식사를 못하면(기아 상태) 죽게 되는데, 이를 막고 철학자들에게 자원을 균등히 분배하는 것이 목표인 과제

<aside>
💡 식사하는 철학자 문제란?
철학자들이 원탁에 앉아있고, 철학자들의 앞에는 스파게티가, 양쪽에는 포크가 놓여있다.
철학자는 양 쪽의 포크를 모두 잡았을 때 식사를 할 수 있다.
이 때 철학자들이 모두 왼쪽 포크만 잡으면 서로 오른쪽 포크를 기다리는 교착상태가 발생한다.

</aside>

## 구현 과정 요약

철학자에 대응하는 스레드 만들기.

포크에 대응하는 뮤텍스 만들기.

철학자의 죽음을 체크하는 모니터 스레드 만들기.

스레드 함수를 실행할 때, 홀수번 스레드는 임의의 대기시간을 주고 시작함.

그러면 짝수가 먼저 식사 후 포크를 놓고 홀수가 바로 포크를 집어 서로 교차하며 포크를 사용하게 된다.

🚨코드가 최신 버전이 아닌 걸 확인.. 다음 번에 클러스터 방문해서 갱신할 것
