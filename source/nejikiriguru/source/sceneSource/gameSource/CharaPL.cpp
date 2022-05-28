#include "CharaPL.h"
#include "DxLib.h"


/*
プレイヤーの処理クラス
ジャンプや落ちる方向等の設定から、プレイヤーのメインループを行っているクラス
*/

//	初期設定：Posを0にセット
CharaPL::CharaPL()
{
	GraphNo = 0;											//	初期化：プレイヤーの見た目種類
	GraphNow = GRAPH::PL_GRAPH::Wait;						//	初期化：画像データのコマ指定
	PosX = 0;												//	初期化：プレイヤーのポジション:X
	PosY = 0;												//	初期化：プレイヤーのポジション:Y
	ProgressVec.Zero();										//	初期化：プレイヤー進行ベクトル
	Buoyancy = 3;											//	初期化：プレイヤーのジャンプによる浮力
	VecX = 1;												//	初期化：プレイヤーの進み方の向き:X
	VecY = 1;												//	初期化：プレイヤーの進み方の向き:Y
	Time = GetNowCount();									//	初期化：現在時刻

	//	画像分割
	for (int GraphX = 0; GraphX < GRAPH::PL_GRAPH::PLLength; GraphX++)
	{
		//	画像の左側から処理

		for (int GraphY = 0; GraphY < 4; GraphY++)
		{
			//	画像の上側から処理
			*pPLGraph[GraphX][GraphY] = 0;							//	初期化：プレイヤーのグラフ
		}
	}
}

//	初期設定：Posを指定
CharaPL::CharaPL(int SetPosX, int SetPosY)
{
	GraphNo = 0;											//	初期化：プレイヤーの見た目種類
	GraphNow = GRAPH::PL_GRAPH::Wait;							//	初期化：画像データのコマ指定
	PosX = SetPosX;											//	初期化：プレイヤーのポジション:X
	PosY = SetPosY;											//	初期化：プレイヤーのポジション:Y
	ProgressVec.Zero();										//	初期化：プレイヤー進行ベクトル
	Buoyancy = 3;											//	初期化：プレイヤーのジャンプによる浮力
	VecX = 1;												//	初期化：プレイヤーの進み方の向き:X
	VecY = 1;												//	初期化：プレイヤーの進み方の向き:Y
	Time = GetNowCount();									//	初期化：現在時刻
}

//	ベクトルの処理
void CharaPL::Vector()
{
	//	ジャンプしていて浮力があるとき
	if (Buoyancy > 0)
	{
		Buoyancy -= 1;									//	浮力を少なくしていく
	}

	ProgressVec.Add(Vector2D(0.0f, (float)((PL_GRAPHVITY - Buoyancy) * VecY)));
}

//	プレイヤーの画像を変化させる
void CharaPL::GraphChange()
{
	//	プレイヤーのモーションで使用する
	int GraOld = GraphNo;

	//	プレイヤーの重力が通常(下向き)の時に
	if (VecY == 1)
	{
		//	上に進んでいる時に
		if (ProgressVec.Y < 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Jump;					//	プレイヤーの画像をジャンプに変更
		}

		//	プレイヤーが横に進んでいない時に
		else if (ProgressVec.X == 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Wait;					//	プレイヤーの画像を待機に変更
		}

		//	プレイヤーが横に進んでいるの時に
		else if (ProgressVec.X != 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Move;					//	プレイヤーの画像を移動に変更
		}
	}

	//	プレイヤーの重力が反転(上向き)の時に
	else
	{
		//	下に進んでいる時に
		if (ProgressVec.Y > 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Jump;					//	プレイヤーの画像をジャンプに変更
		}

		//	プレイヤーが横に進んでいない時に
		else if (ProgressVec.X == 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Wait;					//	プレイヤーの画像を待機に変更
		}

		//	プレイヤーが横に進んでいるの時に
		else if (ProgressVec.X != 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Move;					//	プレイヤーの画像を移動に変更
		}
	}

	//	違う行動の場合最初のコマに指定
	if (GraphNo != GraOld)
	{
		Time = GetNowCount();								//	参照する時間を初期化
		GraphNow = 0;										//	コマを最初に
	}

	//　停止時
	if (GraphNo == GRAPH::PL_GRAPH::Wait && JumpFlag == false)
	{
		//	前の時間から0.25秒後に処理
		if (GetNowCount() - Time > 150)
		{
			Time = GetNowCount();							//	参照する時間を初期化
			GraphNow++;										//	画像のコマを進める

			//	最大値を超えないようにループさせる
			if (GraphNow >= (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = 0;		//	0に設定(ループする)
			}
		}
	}

	//	ジャンプ時
	else if (GraphNo == GRAPH::PL_GRAPH::Jump)
	{
		//	前の時間から0.25秒後に処理
		if (GetNowCount() - Time > 250)
		{
			Time = GetNowCount();							//	参照する時間を初期化
			GraphNow++;										//	画像のコマを進める

			//	最大値で止める
			if (GraphNow > (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = GRAPH::PL_GRAPH::PLLength - 1;		//	最後の値で止める
			}
		}
	}

	//	動くとき
	else if (GraphNo == GRAPH::PL_GRAPH::Move)
	{
		//	前の時間から0.1秒後に処理
		if (GetNowCount() - Time > 100)
		{
			Time = GetNowCount();							//	参照する時間を初期化
			GraphNow++;										//	画像のコマを進める

			//	最大値を超えないようにループさせる
			if (GraphNow >= (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = 0;		//	0に設定(ループする)
			}
		}
	}
}


//	繰り返し実行：プレイヤーの操作の判断と計算
void CharaPL::Update()
{
	ProgressVec.Zero();										//	進行ベクトルをゼロに設定

	KeyboardOperation();

	////	入力がゲームパッドが無効の時
	//if (pPLOperation->GamePadReady == false) { KeyboardOperation(); }	//	キーボードで操作する
	//
	////	入力がゲームパッドが有効の時
	//else { GamePadOperation(); }								//	ゲームパッドで操作する

	Vector();												//	ベクトルの処理
	GraphChange();											//	プレイヤーの画像を変化処理
}

//	表示処理
void CharaPL::Draw()
{
	//	プレイヤーの重力が通常(下向き)の時に
	if (VecY == 1)
	{
		ExtRate = 0;										//	回転を通常
	}

	//	プレイヤーの重力が反転(上向き)の時に
	else
	{
		ExtRate = 1;										//	180度回転させる
	}

	//	プレイヤーの向きの設定
	if (ProgressVec.X != 0)
	{
		//	マイナス方向であれば
		if (ProgressVec.X < 0)
		{
			//	プレイヤーの重力が通常か
			if (VecY == 1)
			{
				PLToFace = true;						//	左
			}
			else
			{
				PLToFace = false;						//	右
			}
		}

		//	プラス方向であれば
		else
		{
			//	プレイヤーの重力が通常か
			if (VecY == 1)
			{
				PLToFace = false;						//	右
			}
			else
			{
				PLToFace = true;						//	左
			}
		}
	}
	//	プレイヤーの表示
	DrawRotaGraph2(
		PosX + WIN_UI_WIDTH,								//	ゲーム画面に収まるようにXを決める
		PosY + WIN_UI_HEIGHT,								//	ゲーム画面に収まるようにYを決める
		PL_GRAPH_SIZE / 2, PL_GRAPH_SIZE / 2,				//	中心位置は画像の中央
		PLSize, PI * ExtRate,							//	大きさ・向きを指定
		*pPLGraph[GraphNow][GraphNo], true, PLToFace);	//	表示する画像を種類・コマから参照
}

//	更新処理を段階化	プレイヤーの位置を確認しなおす
void CharaPL::DataRoad(MAP_INFO::Stage MapData, Vector2D PLPos)
{
	PosX = (int)PLPos.X;									//	プレイヤーのX軸を設定
	PosY = (int)PLPos.Y;									//	プレイヤーのY軸を設定
	Buoyancy = PL_GRAPHVITY;									//	重力を相殺して0に
	VecX = 1;												//	進む意識の方向を通常に
	VecY = 1;												//	重力の方向を通常に
	NowMapData = MapData;									//	判定するステージデータを読み込み
}

//	プレイヤーを反転させる X:0 Y:1
void CharaPL::PLAnti(int XorY)
{
	//	Xの反転を指定された場合
	if (XorY == 0) { VecX *= -1; }							//	進むXを反転

	//	Yの反転を指定された場合
	else if (XorY == 1) { VecY *= -1; }						//	重力Yを反転
}

//	//	キーボードでの操作
void CharaPL::KeyboardOperation()
{
	//	プレイヤーがジャンプできるかどうか
	if (JumpFlag == false && (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaJump)
		|| (VecY > 0 && pPLOperation->GetOperation(OPERATION_CATEGORY::CharaUP))
		|| (VecY < 0 && pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDown))))
	{
		//	ジャンプしていなくてスペースキーを押している
		Buoyancy = PL_GRAPHVITY + 13;						//	ジャンプ力：1.5ブロック分飛ぶ
		JumpFlag = true;									//	ジャンプをした
		pPLSE->SoundPlay(SOUND_NAME::Jump);					//	音を再生(ジャンプ)
		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	音を停止(歩く音)
	}

	//	進行方向:右左同時押し:なし
	if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaLeft) &&
		pPLOperation->GetOperation(OPERATION_CATEGORY::CharaRight))
	{
		pPLSE->SoundFinal(SOUND_NAME::FootStep);		//	音を停止(歩く音)
	}

	//	進行方向:左右どちらかで移動
	else if (pPLOperation->Joystick[1][0] >= 0.25 || pPLOperation->Joystick[1][0] <= -0.25)
	{
		ProgressVec.Add(Vector2D(
			(PL_MOV_SPEED * pPLOperation->Joystick[1][0] * VecX),	//	ジョイスティックの傾き具合でプレイヤーの速度が変化
			0.0));											//	高さの変更はなし

		//	ジャンプしていない時:音を再生(歩く音)
		if (JumpFlag == false)pPLSE->SoundPlay(SOUND_NAME::FootStep);

		//	ジャンプしている時:音を停止(歩く音)
		else pPLSE->SoundFinal(SOUND_NAME::FootStep);
	}
	//	進行方向:左ボタン押し
	else if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaLeft))
	{
		//	ダッシュ時
		if (!pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDash))
		{
			ProgressVec.Add(Vector2D((float)(-PL_MOV_SPEED * VecX), 0.0));			//	進行ベクトルにスピード分追加
		}
		else
		{
			ProgressVec.Add(Vector2D((float)(-PL_MOV_SPEED * VecX) / 2, 0.0f));				//	進行ベクトルにスピード分追加
		}
		//	ジャンプしていない時
		if (JumpFlag == false) {
			pPLSE->SoundPlay(SOUND_NAME::FootStep);			//	音を再生(歩く音)
		}

	}
	//	進行方向:右ボタン押し
	else if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaRight))
	{
		//	ダッシュ時
		if (!pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDash))
		{
			ProgressVec.Add(Vector2D((float)(PL_MOV_SPEED * VecX), 0.0f));				//	進行ベクトルにスピード分追加
		}
		else
		{
			ProgressVec.Add(Vector2D((float)(PL_MOV_SPEED * VecX) / 2, 0.0f));				//	進行ベクトルにスピード分追加
		}
		//	ジャンプしていない時
		if (JumpFlag == false) {
			pPLSE->SoundPlay(SOUND_NAME::FootStep);			//	音を再生(歩く音)
		}

	}
	//	何もしていない
	else
	{
		ProgressVec.Zero();									//	進行ベクトルを0ベクトルに
		ExtRate = 0;										//	回転をしていないように
		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	音を停止(歩く音)
	}
}

//	ゲームパッドでの操作
//void CharaPL::GamePadOperation()
//{
//	//	プレイヤーがジャンプできるかどうか
//	if (pPLGamePad->OneButton(XINPUT_BUTTON_A) && JumpFlag == false)
//	{
//		//	ジャンプしていなくてスペースキーを押している
//		Buoyancy = PL_GRAPHVITY + 13;						//	ジャンプ力：1.5ブロック分飛ぶ
//		JumpFlag = true;									//	ジャンプをした
//		pPLSE->SoundPlay(SOUND_NAME::Jump);					//	音を再生(ジャンプ)
//	}
//
//	//	進行方向:左右どちらかで移動
//	if (pPLGamePad->Joystick[1][0] >= 0.25 || pPLGamePad->Joystick[1][0] <= -0.25)
//	{
//		ProgressVec.Add(Vector2D(
//			(PL_MOV_SPEED * pPLGamePad->Joystick[1][0] * VecX),	//	ジョイスティックの傾き具合でプレイヤーの速度が変化
//			0.0));											//	高さの変更はなし
//
//		//	ジャンプしていない時:音を再生(歩く音)
//		if (JumpFlag == false)pPLSE->SoundPlay(SOUND_NAME::FootStep);
//		
//		//	ジャンプしている時:音を停止(歩く音)
//		else pPLSE->SoundFinal(SOUND_NAME::FootStep);
//	}
//
//	//	何もしていない
//	else
//	{
//		ProgressVec.Zero();									//	進行ベクトルを0ベクトルに
//		ExtRate = 0;										//	回転をしていないように
//		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	音を停止(歩く音)
//	}
//}


void CharaPL::SetMove()
{
	// 移動量に基づいてプレイヤークタの座標を移動
	CharMove(&PosX, &PosY,
		&Buoyancy,
		(int)ProgressVec.X, (int)ProgressVec.Y,
		PL_GRAPH_SIZE * 2, &JumpFlag);
}

// マップとの当たり判定
int CharaPL::CharMove(int* pPosX, int* pPosY, int* pDownSP, int MoveX, int MoveY, int Size, bool* pJumpFlag)
{
	int Dummy = 0;
	int PLMoveSize = Size / 2;

	//	重力に対応させる
	int PLMoveTop, PLMoveBottom;

	//	下に落ちる
	if (VecY == 1)
	{
		PLMoveTop = *pPosY - PLMoveSize + 24;
		PLMoveBottom = *pPosY + PLMoveSize;
	}

	//	上に落ちる
	else
	{
		PLMoveTop = *pPosY - PLMoveSize - 1;
		PLMoveBottom = *pPosY + PLMoveSize - 25;
	}

	// プレイヤーの左上、右上、左下、右下部分が当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する

	// 先ず上下移動成分だけでチェック
	{
		// 左下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveBottom, &Dummy, &MoveY) == HIT_RESULT::Top)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// 右下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveBottom, &Dummy, &MoveY) == HIT_RESULT::Top)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// 左上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveTop, &Dummy, &MoveY) == HIT_RESULT::Bottom)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// 右上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveTop, &Dummy, &MoveY) == HIT_RESULT::Bottom)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// 上下移動成分を加算
		*pPosY += MoveY;
	}

	// 後に左右移動成分だけでチェック
	{
		// 左下のチェック
		MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveBottom, &MoveX, &Dummy);

		// 右下のチェック
		MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveBottom, &MoveX, &Dummy);

		// 左上のチェック
		MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveTop, &MoveX, &Dummy);

		// 右上のチェック
		MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveTop, &MoveX, &Dummy);

		// 左右移動成分を加算
		*pPosX += MoveX;
	}

	// 接地判定
	{
		if (VecY == 1)
		{
			// プレイヤーの左下と右下の下に地面があるか調べる
			if (GetChipParam(*pPosX - (Size * 0.5f) + 10, *pPosY + (Size * 0.5f) + 1) == 0 &&
				GetChipParam(*pPosX + (Size * 0.5f) - 10, *pPosY + (Size * 0.5f) + 1) == 0)
			{
				// 足場が無かったらジャンプ中にする
				*pJumpFlag = true;
			}
			else
			{
				// 足場が在ったら接地中にする
				*pJumpFlag = false;

			}
		}

		//	上に落ちる
		else
		{
			// プレイヤーの左下と右下の下に地面があるか調べる
			if (GetChipParam(*pPosX - (Size * 0.5f) + 10, *pPosY + -(Size * 0.5f) - 2) == 0 &&
				GetChipParam(*pPosX + (Size * 0.5f) - 10, *pPosY + -(Size * 0.5f) - 2) == 0)
			{
				// 足場が無かったらジャンプ中にする
				*pJumpFlag = true;
			}
			else
			{
				// 足場が在ったら接地中にする
				*pJumpFlag = false;

			}
		}
	}

	// 終了
	return 0;
}

//	当たっているブロック判定
HIT_RESULT CharaPL::MapHitCheck(int PosX, int PosY, int* pMoveX, int* pMoveY)
{
	int AfterX, AfterY;

	// 移動量を足す
	AfterX = PosX + *pMoveX;
	AfterY = PosY + *pMoveY;

	// 当たり判定のあるブロックに当たっているかチェック
	if (GetChipParam((float)AfterX, (float)AfterY) != GRAPH::BLOCK::Ear)
	{
		float BlockLeftX, BlockTopY, BlockRightX, BlockBottomY;

		// 当たっていたら壁から離す処理を行う

		// ブロックの上下左右の座標を算出
		BlockLeftX = (float)((int)AfterX / (MAP_CHIP_SIZE * 2)) * MAP_CHIP_SIZE * 2;			// 左辺の X 座標
		BlockRightX = (float)(((int)AfterX / (MAP_CHIP_SIZE * 2)) + 1) * MAP_CHIP_SIZE * 2;	// 右辺の X 座標

		BlockTopY = (float)((int)AfterY / (MAP_CHIP_SIZE * 2)) * MAP_CHIP_SIZE * 2;			// 上辺の Y 座標
		BlockBottomY = (float)(((int)AfterY / (MAP_CHIP_SIZE * 2)) + 1) * MAP_CHIP_SIZE * 2;	// 下辺の Y 座標


		// 上辺に当たっていた場合
		if (*pMoveY > 0)
		{
			// 移動量を補正する
			*pMoveY = (int)(BlockTopY - PosY - 1);

			// 上辺に当たったと返す
			return HIT_RESULT::Top;
		}

		// 下辺に当たっていた場合
		if (*pMoveY < 0)
		{
			// 移動量を補正する
			*pMoveY = (int)(BlockBottomY - PosY + 0);

			// 下辺に当たったと返す
			return HIT_RESULT::Bottom;
		}

		// 左辺に当たっていた場合
		if (*pMoveX > 0)
		{
			// 移動量を補正する
			*pMoveX = (int)(BlockLeftX - PosX - 1);

			// 左辺に当たったと返す
			return HIT_RESULT::Left;
		}

		// 右辺に当たってい た場合
		if (*pMoveX < 0)
		{
			// 移動量を補正する
			*pMoveX = (int)(BlockRightX - PosX + 1);

			// 右辺に当たったと返す
			return HIT_RESULT::Right;
		}

		// ここに来たら適当な値を返す
		return HIT_RESULT::Bottom;
	}

	// どこにも当たらなかったと返す
	return HIT_RESULT::None;
}

// マップから抽出
int CharaPL::GetChipParam(float ParamX, float ParamY)
{
	// 整数値へ変換
	int IntX = (int)(ParamX) / (MAP_CHIP_SIZE * 2);
	int IntY = (int)(ParamY) / (MAP_CHIP_SIZE * 2);

	// マップからはみ出ていたら 1 を返す
	if (IntX >= MAP_WIDTH || IntY >= MAP_HEIGHT || IntX < 0 || IntY < 0)
	{
		return 1;
	}

	// 指定の座標に該当するマップの情報を返す
	return NowMapData.BlockData[IntY][IntX];
}