#include <stdio.h>
#include <math.h>

int main() {
	int angle = 0, floor = 0, frame = 0, fpf = 0;
	double bpm = 0, fs = 0, time = 0, offset = 0, namoji = 0, currentangle = 0;
	char ext[10];
	
	FILE* fp;
	fopen_s(&fp, "animation.txt", "a");
	if (fp == NULL) printf("���� ���� ����\n"); else printf("���� ���� ����\n");
	printf("ADOFAI Animator 1.0 made by Pangu\n������ȭ�� �׸� ������ \"1,2,3,4\"�� ���� ���ڷθ� �Ǿ� �־�� �մϴ�.\n�׸� ���� Ȯ���� �Է�:");
	scanf_s("%s", ext, 10);
	printf("�⺻ BPM �Է�:");
	scanf_s("%lf", &bpm);	
	printf("������ �� ���� �Է�(s):");
	scanf_s("%lf", &fs);
	printf("������ �Է�:");
	scanf_s("%lf", &offset);
	fprintf(fp, "%s","���ο� �ִϸ��̼�\n\n");//new animation	
	frame = offset / fs + 2;//������ 1���� �����ϴϱ� 1 ���ϰ�, n������ '����'�� �ǹ̰� �־����� 1 ����.  
	//�����¸�ŭ ������ ����
	namoji = fmod(offset, fs);

	printf("ù Ÿ�ϰ� �� ��° Ÿ�� ������ ������ 180�� �����̹Ƿ� �ڵ����� ó���˴ϴ�.\n �ι�° Ÿ�Ϻ��� �Է��� �ּ���.\n");

	while (1) {
		printf("������ �Է��ϼ���(0 ������ �� �Է½� ���� ��� ����, �뷡�� ���� �� ������ ���� ���� �Է¹ٶ�)\n����:");
		scanf_s("%d", &angle);
		if (angle <= 0)
		{
			printf("���� ���. BPM�� �Է��ϼ���(0 ������ �� �Է½� ���α׷� ����):");
			scanf_s("%lf", &bpm);
			if (bpm <= 0) {
				printf("���α׷��� �����մϴ�.");
				return 0;
			}
			else
				continue;
		}
		floor++;
		time = (double)angle/bpm /3 + fs - namoji;//�� ������ �ð� ��� 
		currentangle = 3 * bpm * (fs - namoji);// ���� �ð���ŭ ���� ������ �ʱ� �����ϱ�
		fpf = time / fs;
		namoji = fmod(time, fs);
		for (int i = 0; i < fpf; i++) {
			fprintf(fp, "{ \"floor\": %d, \"eventType\" : \"CustomBackground\", \"color\" : \"ffffff\", \"bgImage\" : \"%d.png\", \"imageColor\" : \"ffffff\", \"parallax\" : [100, 100], \"bgDisplayMode\" : \"FitToScreen\", \"loopBG\" : \"Disabled\", \"unscaledSize\" : 100, \"angleOffset\" : %lf },\n", floor, frame, currentangle);
			frame++;
			currentangle += 3 * bpm * fs;
		}

	}
	fclose(fp);
	return 0;
}