
#include "main.h"
#include "propexplosion.h"

#define PI					3.1415927f			// �~����
#define ROT_SPEED			( PI / 100.0f )		// ��]���x
#define R					1.0f				// �}�`�̑傫��
#define CORNER_NUM			20					// �p��
#define MAX_EXPLOSION_NUM	1					// �ő唚����
#define EXPLOSION_INTERVAL	200					// �����̔����Ԋu(�~���b�P��)
#define EXPLOSION_AREA		4.0f				// �����̔����͈�
#define EXPLOSION_SPEED		0.05f				// �����̊g�呬�x
#define EXPLOSION_R1		1.0f				// ���邳�������n�߂锼�a
#define EXPLOSION_R2		2.0f				// ���ł��锼�a

Explosion		exExplode[MAX_EXPLOSION_NUM];	// �����o�b�t�@





int MakeSphereIndexed( CUSTOMVERTEX *pVertices, int *pVertexNum,
					   WORD *pIndices, int *pIndexNum )		// ���̍쐬(�C���f�b�N�X�t��)
{
	int					i, j;
	float				fTheta;
	float				fPhi;
	float				fAngleDelta;
	int					nIndex;						// �f�[�^�̃C���f�b�N�X
	int					nIndexY;					// x�����C���f�b�N�X

	// ���_�f�[�^�쐬
	fAngleDelta = 2.0f * PI / CORNER_NUM;
	nIndex = 0;
	fTheta = 0.0f;
	for ( i = 0; i < CORNER_NUM / 4 + 1; i++ ) {
		fPhi = 0.0f;
		for ( j = 0; j < CORNER_NUM + 1; j++ ) {
			pVertices[nIndex].v4Pos  = XMFLOAT4( R * sinf( fTheta ) * cosf( fPhi ),
												 R * cosf( fTheta ),
												 R * sinf( fTheta ) * sinf( fPhi ), 1.0f );
			pVertices[nIndex].v2UV = XMFLOAT2( fPhi / ( 2.0f * PI ), fTheta / PI );
			nIndex++;
			fPhi += fAngleDelta;
		}
		fTheta += fAngleDelta;
	}
	*pVertexNum = nIndex;

	// �C���f�b�N�X�f�[�^�쐬
	nIndex = 0;
	for ( i = 0; i < CORNER_NUM; i++ ) {
		for ( j = 0; j < CORNER_NUM / 4; j++ ) {
			nIndexY = j * ( CORNER_NUM + 1 );
			pIndices[nIndex    ] = nIndexY + i;
			pIndices[nIndex + 1] = nIndexY + ( CORNER_NUM + 1 ) + i;
			pIndices[nIndex + 2] = nIndexY + i + 1;
			nIndex += 3;
			pIndices[nIndex    ] = nIndexY + i + 1;
			pIndices[nIndex + 1] = nIndexY + ( CORNER_NUM + 1 ) + i;
			pIndices[nIndex + 2] = nIndexY + ( CORNER_NUM + 1 ) + i + 1;
			nIndex += 3;
		}
	}
	*pIndexNum = nIndex;

	return 0;
}


// �����̓���
int MoveExplosion( void )
{
	int					i;
	//int					nNowTime;				// ���̎���(�����Ԋu�x�[�X)
	static int			nLastTime = 0;			// �O�̎���(�����Ԋu�x�[�X)
	float				x, z;					// x, z���W

	// �����̔���

		for ( i = 0; i < MAX_EXPLOSION_NUM; i++ )
		{
			if ( !exExplode[i].bActive ) {
				exExplode[i].bActive = true;
				exExplode[i].nTime = 0;
				x = ( rand() * EXPLOSION_AREA / RAND_MAX - EXPLOSION_AREA / 2.0f );
				z = ( rand() * EXPLOSION_AREA / RAND_MAX - EXPLOSION_AREA / 2.0f );
				exExplode[i].v3CenterPos = XMFLOAT3( x, 0.0f, z );
				exExplode[i].fAngle = 0.0f;
				exExplode[i].fBright = 1.0f;
				exExplode[i].fRadius = 0.1f;
				exExplode[i].matMatrix = XMMatrixIdentity();
				break;
			}
		}

	// �����̐���
	for ( i = 0; i < MAX_EXPLOSION_NUM; i++ ) {
		if ( exExplode[i].bActive ) {
			exExplode[i].fRadius += EXPLOSION_SPEED;
			if ( exExplode[i].fRadius > EXPLOSION_R2 ) {
				exExplode[i].bActive = false;
			}
			else {
				if ( exExplode[i].fRadius > EXPLOSION_R1 ) {
					exExplode[i].fBright = ( EXPLOSION_R2 - exExplode[i].fRadius ) /
										   ( EXPLOSION_R2 - EXPLOSION_R1 );
				}
				exExplode[i].matMatrix._11 = exExplode[i].fRadius;
				exExplode[i].matMatrix._22 = exExplode[i].fRadius;
				exExplode[i].matMatrix._33 = exExplode[i].fRadius;
				exExplode[i].matMatrix._41 = exExplode[i].v3CenterPos.x;
				exExplode[i].matMatrix._42 = exExplode[i].v3CenterPos.y;
				exExplode[i].matMatrix._43 = exExplode[i].v3CenterPos.z;
			}
		}
	}

	return 0;
}
