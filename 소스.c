#include <stdio.h>
#include <math.h>

int main() {
	int angle = 0, floor = 0, frame = 0, fpf = 0;
	double bpm = 0, fs = 0, time = 0, offset = 0, namoji = 0, currentangle = 0;
	char ext[10];
	
	FILE* fp;
	fopen_s(&fp, "animation.txt", "a");
	if (fp == NULL) printf("파일 열기 실패\n"); else printf("파일 열기 성공\n");
	printf("ADOFAI Animator 1.0 made by Pangu\n프레임화된 그림 파일은 \"1,2,3,4\"와 같이 숫자로만 되어 있어야 합니다.\n그림 파일 확장자 입력:");
	scanf_s("%s", ext, 10);
	printf("기본 BPM 입력:");
	scanf_s("%lf", &bpm);	
	printf("프레임 간 간격 입력(s):");
	scanf_s("%lf", &fs);
	printf("오프셋 입력:");
	scanf_s("%lf", &offset);
	fprintf(fp, "%s","새로운 애니메이션\n\n");//new animation	
	frame = offset / fs + 2;//프레임 1부터 시작하니까 1 더하고, n프레임 '다음'에 의미가 있어져서 1 더함.  
	//오프셋만큼 프레임 빼기
	namoji = fmod(offset, fs);

	printf("첫 타일과 두 번째 타일 사이의 간격은 180도 고정이므로 자동으로 처리됩니다.\n 두번째 타일부터 입력해 주세요.\n");

	while (1) {
		printf("각도를 입력하세요(0 이하의 값 입력시 변속 모드 진입, 노래가 끝날 때 가급적 높은 정수 입력바람)\n각도:");
		scanf_s("%d", &angle);
		if (angle <= 0)
		{
			printf("변속 모드. BPM을 입력하세요(0 이하의 값 입력시 프로그램 종료):");
			scanf_s("%lf", &bpm);
			if (bpm <= 0) {
				printf("프로그램을 종료합니다.");
				return 0;
			}
			else
				continue;
		}
		floor++;
		time = (double)angle/bpm /3 + fs - namoji;//한 박자의 시간 재기 
		currentangle = 3 * bpm * (fs - namoji);// 남은 시간만큼 각도 오프셋 초기 설정하기
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